#pragma once

#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include <array>
#include <vector>
#include "RenderPassManager.hpp"
#include "../utils/utils.hpp"

namespace RS{
	class FrameBufferInfo {
	public:
		RenderPassInfo renderpass;
		uint32_t width;
		uint32_t height;
		uint32_t layers;
		std::vector<vk::ImageView> imageviews;
		bool operator==(const FrameBufferInfo& rhs) const;
	};


	struct FrameBufferInfoHash {
		size_t operator()(const FrameBufferInfo& k) const;
	};

	class ResourceManager;
	class RenderPassManager;
	class FrameBufferManager {
	private:
		ResourceManager& resourcemanager;
		RenderPassManager& renderpassmanager;
		std::unordered_map<FrameBufferInfo, std::array<vk::Framebuffer, 2>, FrameBufferInfoHash> framebuffers;
	public:
		FrameBufferManager(ResourceManager& resourcemanager);
		void destroy();
		~FrameBufferManager() = default;
		std::array<vk::Framebuffer, 2> createFrameBuffers(const FrameBufferInfo& info);
		std::array<vk::Framebuffer, 2> getFrameBuffers(const FrameBufferInfo& info);
	};
}