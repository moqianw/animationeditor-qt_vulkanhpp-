#include "FrameBufferManager.hpp"
#include "ResourceManager.hpp"
namespace RS{

	bool FrameBufferInfo::operator==(const FrameBufferInfo& rhs) const
	{
		return renderpass == rhs.renderpass &&
			width == rhs.width &&
			height == rhs.height &&
			layers == rhs.layers &&
			imageviews == rhs.imageviews;
	}
	size_t FrameBufferInfoHash::operator()(const FrameBufferInfo& k) const
	{
		size_t h = 0;
		UT::hashCombine(h, RenderPassInfoHash{}(k.renderpass));
		UT::hashCombine(h, k.width);
		UT::hashCombine(h, k.height);
		UT::hashCombine(h, k.layers);
		for (auto& iv : k.imageviews) {
			UT::hashCombine(h, reinterpret_cast<size_t>(static_cast<VkImageView>(iv)));
		}
		return h;
	}
	FrameBufferManager::FrameBufferManager(ResourceManager& resourcemanager):resourcemanager(resourcemanager),
		renderpassmanager(resourcemanager.renderpassmanager)
	{
	}

	std::array<vk::Framebuffer, 2> FrameBufferManager::createFrameBuffers(const FrameBufferInfo& info)
	{
		auto device = resourcemanager.getDevice();
		auto renderpass = renderpassmanager.getRenderPass(info.renderpass);
		vk::FramebufferCreateInfo createinfo;
		createinfo
			.setHeight(info.height)
			.setLayers(info.layers)
			.setRenderPass(renderpass)
			.setWidth(info.width);
		std::array<vk::Framebuffer, 2> framebufferarr;
		for (size_t i = 0; i < framebufferarr.size(); i++) {
			std::vector<vk::ImageView> imageviews = info.imageviews;
			createinfo.setAttachments(imageviews); // µ¥ÔªËØ vector
			framebufferarr[i] = device.createFramebuffer(createinfo);
		}
		return std::array<vk::Framebuffer, 2>();
	}
	std::array<vk::Framebuffer, 2> FrameBufferManager::getFrameBuffers(const FrameBufferInfo& info)
	{
		auto iter = framebuffers.find(info);
		if(iter != framebuffers.end()) {
			return iter->second;
		}
		else {
			return createFrameBuffers(info);
		}
	}


	void FrameBufferManager::destroy()
	{
		if (vk::Device device = resourcemanager.getDevice()) {
			for (auto& [info, framebufferarr] : framebuffers) {
				for (auto& framebuffer : framebufferarr) {
					if (framebuffer) device.destroyFramebuffer(framebuffer);
				}
			}
			framebuffers.clear();
		}
	}


}