#pragma once
#include <vulkan/vulkan.hpp>
#include "utils/utils.hpp"

class VulkanRenderer_;
using VulkanRenderer = std::unique_ptr<VulkanRenderer_>;

class VulkanRendererCreateInfo {
public:
	VulkanRendererCreateInfo& setDevice(const vk::Device& device) {
		this->device = device;
		return *this;
	}
	VulkanRendererCreateInfo& setRenderPass(const vk::RenderPass& renderpass) {
		this->renderpass = renderpass;
		return *this;
	}
private:
	friend class VulkanRenderer_;
	vk::Device device;
	vk::RenderPass renderpass;
	
};
class VulkanRenderer_ {
public:
	VulkanRenderer_();
	VulkanRenderer_(const VulkanRendererCreateInfo& createinfo);
	~VulkanRenderer_();
protected:
private:
	vk::Device device;
	vk::RenderPass renderpass;
	std::vector<UT::Frame> frames;
	uint32_t currentframe;
};