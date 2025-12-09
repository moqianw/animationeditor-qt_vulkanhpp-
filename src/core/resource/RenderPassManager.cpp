#include "RenderPassManager.hpp"
#include "ResourceManager.hpp"
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
		vk::AttachmentDescription attachment;
		vk::SubpassDependency dependency;
		vk::SubpassDescription subpass;
		attachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR)
			.setFormat(info.colorFormat)
			.setInitialLayout(vk::ImageLayout::eUndefined)
			.setLoadOp(vk::AttachmentLoadOp::eClear)
			.setSamples(info.samples)
			.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
			.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
			.setStoreOp(vk::AttachmentStoreOp::eStore);
		dependency
			.setSrcSubpass(VK_SUBPASS_EXTERNAL)
			.setDstSubpass(0)
			.setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
			.setSrcAccessMask(vk::AccessFlagBits::eNone)
			.setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
			.setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);

		subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
			.setColorAttachments(
				vk::AttachmentReference()
				.setAttachment(0)
				.setLayout(vk::ImageLayout::eColorAttachmentOptimal));

		//深度附件

		vk::AttachmentDescription depthattachment;
		depthattachment.setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal)
			.setFormat(info.depthFormat)
			.setInitialLayout(vk::ImageLayout::eUndefined)
			.setLoadOp(vk::AttachmentLoadOp::eClear)
			.setSamples(info.samples)
			.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
			.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
			.setStoreOp(vk::AttachmentStoreOp::eStore);
		vk::AttachmentReference depthAttachmentRef;
		depthAttachmentRef.setAttachment(1)  // 假设 color attachment 是 0
			.setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal);

		subpass
			.setPDepthStencilAttachment(&depthAttachmentRef);
		std::vector<vk::AttachmentDescription> attachments = { attachment,depthattachment };
		createinfo
			.setAttachmentCount(2)
			.setAttachments(attachments)
			.setDependencyCount(1)
			.setDependencies({ dependency })
			.setSubpassCount(1)
			.setSubpasses({ subpass });
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
}