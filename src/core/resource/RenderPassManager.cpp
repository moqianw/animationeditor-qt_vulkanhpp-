#include "RenderPassManager.hpp"

#include "ResourceManager.hpp"
#include "../utils/utils.hpp"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../engine/Mapping.hpp"
namespace RS {
	RenderPassManager::RenderPassManager(ResourceManager& resourcemanager) :resourcemanager(resourcemanager)
	{
	}
	void RenderPassManager::destroy() {
		if (vk::Device device = resourcemanager.getDevice()) {
			for (auto& [info, renderpass] : renderpasses) {
				if (renderpass) device.destroyRenderPass(renderpass);
			}
			renderpasses.clear();
		}
	}
	vk::RenderPass RenderPassManager::createRenderPass(const RenderPassInfo& info) {
		vk::RenderPassCreateInfo createinfo;
		std::vector<vk::AttachmentDescription> attachments;
		for(auto& attachmentinfo:info.attachments){
			vk::AttachmentDescription attachment;
			attachment.setFinalLayout(attachmentinfo.finalLayout)
				.setFormat(attachmentinfo.format)
				.setInitialLayout(attachmentinfo.initialLayout)
				.setLoadOp(attachmentinfo.loadOp)
				.setSamples(attachmentinfo.samples)
				.setStencilLoadOp(attachmentinfo.stencilLoadOp)
				.setStencilStoreOp(attachmentinfo.stencilStoreOp)
				.setStoreOp(attachmentinfo.storeOp);
			attachments.push_back(attachment);
		}

		std::vector<vk::SubpassDescription> subpass;
		std::vector<vk::AttachmentReference> depthrefs;
		depthrefs.resize(info.subpasses.size());
		for (int i = 0; i < info.subpasses.size();++i) {
			auto& subpassinfo = info.subpasses[i];
			vk::SubpassDescription subpassdesc;
			std::vector<vk::AttachmentReference> colorRefs;
			for (auto& colorrefinfo : subpassinfo.colorRefs) {
				vk::AttachmentReference colorref;
				colorref.setAttachment(colorrefinfo.attachment)
					.setLayout(colorrefinfo.layout);
				colorRefs.push_back(colorref);
			}
			subpassdesc.setPipelineBindPoint(subpassinfo.bindpoint)
				.setColorAttachments(colorRefs);

			if (subpassinfo.depthRef.has_value()) {

				depthrefs[i].setAttachment(subpassinfo.depthRef->attachment)
					.setLayout(subpassinfo.depthRef->layout);
				subpassdesc.setPDepthStencilAttachment(&depthrefs[i]);
			}
			subpass.push_back(subpassdesc);
		}
		std::vector<vk::SubpassDependency> dependencies;
		for (auto& dependencyinfo : info.dependencies) {
			vk::SubpassDependency dependency;
			dependency.setSrcSubpass(dependencyinfo.srcSubpass)
				.setDstSubpass(dependencyinfo.dstSubpass)
				.setSrcStageMask(dependencyinfo.srcStageMask)
				.setDstStageMask(dependencyinfo.dstStageMask)
				.setSrcAccessMask(dependencyinfo.srcAccessMask)
				.setDstAccessMask(dependencyinfo.dstAccessMask);
			dependencies.push_back(dependency);
		}

		createinfo
			.setAttachmentCount(attachments.size())
			.setAttachments(attachments)
			.setDependencyCount(dependencies.size())
			.setDependencies(dependencies)
			.setSubpassCount(subpass.size())
			.setSubpasses(subpass);
		auto renderpass = resourcemanager.getDevice().createRenderPass(createinfo);
		if (!renderpass) throw std::runtime_error("create renderpass false");
		renderpasses.insert({ info,renderpass });
		return renderpass;
	}
	vk::RenderPass RenderPassManager::getRenderPass(const RenderPassInfo& info) {
		auto iter = renderpasses.find(info);
		if (iter != renderpasses.end()) {
			return iter->second;
		}
		else {
			return createRenderPass(info);
		}
	}
	bool RenderPassInfo::operator==(const RenderPassInfo& rhs) const {
		return attachments == rhs.attachments &&
			subpasses == rhs.subpasses &&
			dependencies == rhs.dependencies;
	}
	size_t RenderPassInfoHash::operator()(const RenderPassInfo& k) const {
		size_t h = 0;
		for (auto& attachment : k.attachments) {
			UT::hashCombine(h, static_cast<size_t>(attachment.finalLayout));
			UT::hashCombine(h, static_cast<size_t>(attachment.format));
			UT::hashCombine(h, static_cast<size_t>(attachment.initialLayout));
			UT::hashCombine(h, static_cast<size_t>(attachment.loadOp));
			UT::hashCombine(h, static_cast<size_t>(attachment.storeOp));
			UT::hashCombine(h, static_cast<size_t>(attachment.samples));

		}
		for (auto& subpass : k.subpasses) {
			UT::hashCombine(h, static_cast<size_t>(subpass.bindpoint));
			for (auto& colorref : subpass.colorRefs) {
				UT::hashCombine(h, static_cast<size_t>(colorref.attachment));
				UT::hashCombine(h, static_cast<size_t>(colorref.layout));
			}
			if (subpass.depthRef.has_value()) {
				UT::hashCombine(h, static_cast<size_t>(subpass.depthRef->attachment));
				UT::hashCombine(h, static_cast<size_t>(subpass.depthRef->layout));
			}
		}
		for (auto& dependency : k.dependencies) {
			UT::hashCombine(h, static_cast<size_t>(dependency.srcSubpass));
			UT::hashCombine(h, static_cast<size_t>(dependency.dstSubpass));
			UT::hashCombine(h, static_cast<size_t>(VkPipelineStageFlags(dependency.srcStageMask)));
			UT::hashCombine(h, static_cast<size_t>(VkPipelineStageFlags(dependency.dstStageMask)));
			UT::hashCombine(h, static_cast<size_t>(VkPipelineStageFlags(dependency.srcAccessMask)));
			UT::hashCombine(h, static_cast<size_t>(VkPipelineStageFlags(dependency.dstAccessMask)));
		}
		return h;
	}
	bool RenderPassInfo::AttachmentDesc::operator==(const AttachmentDesc& rhs) const {
		return format == rhs.format &&
			samples == rhs.samples &&
			loadOp == rhs.loadOp &&
			storeOp == rhs.storeOp &&
			initialLayout == rhs.initialLayout &&
			finalLayout == rhs.finalLayout &&
			stencilLoadOp == rhs.stencilLoadOp &&
			stencilStoreOp == rhs.stencilStoreOp;
	}
	bool RenderPassInfo::SubpassDesc::operator==(const SubpassDesc& rhs) const {
		return bindpoint == rhs.bindpoint &&
			colorRefs == rhs.colorRefs &&
			depthRef == rhs.depthRef;
	}
	bool RenderPassInfo::SubpassDependencyDesc::operator==(const SubpassDependencyDesc& rhs) const {
		return srcSubpass == rhs.srcSubpass &&
			dstSubpass == rhs.dstSubpass &&
			srcStageMask == rhs.srcStageMask &&
			dstStageMask == rhs.dstStageMask &&
			srcAccessMask == rhs.srcAccessMask &&
			dstAccessMask == rhs.dstAccessMask;
	}



	bool RenderPassInfo::AttachmentReference::operator==(const AttachmentReference& rhs) const
	{
		return attachment == rhs.attachment &&
			layout == rhs.layout;
	}

}


namespace RS {
	RenderPassInfo RenderPassLoader::loadFromFile(const std::string& filepath)
	{
		RenderPassInfo renderpassinfo;

		QFile file(QString::fromStdString(filepath));
		if (!file.open(QIODevice::ReadOnly)) {
			throw std::runtime_error("Failed to open renderpass file: " + filepath);
		}
		QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
		if(!doc.isObject()) throw std::runtime_error("Invalid JSON file");

		QJsonObject object = doc.object();
		QJsonArray attachmentarray = object["attachments"].toArray();
		for (auto attachmentinfo : attachmentarray) {
			QJsonObject infoobject = attachmentinfo.toObject();
			RenderPassInfo::AttachmentDesc attachment;
			attachment.format = EG::stringToVkFormat(infoobject["format"].toString().toStdString());
			attachment.initialLayout = EG::stringToVkImageLayout(infoobject["initialLayout"].toString().toStdString());
			attachment.finalLayout = EG::stringToVkImageLayout(infoobject["finalLayout"].toString().toStdString());
			attachment.loadOp = EG::stringToVkAttachmentLoadOp(infoobject["loadOp"].toString().toStdString());
			attachment.storeOp = EG::stringToVkAttachmentStoreOp(infoobject["storeOp"].toString().toStdString());
			attachment.stencilLoadOp =EG::stringToVkAttachmentLoadOp(infoobject["stencilLoadOp"].toString().toStdString());
			attachment.stencilStoreOp =EG::stringToVkAttachmentStoreOp(infoobject["stencilStoreOp"].toString().toStdString());
			attachment.samples = static_cast<vk::SampleCountFlagBits>(infoobject["samples"].toInt());
			renderpassinfo.attachments.push_back(attachment);
		}
		return renderpassinfo;
	}
}