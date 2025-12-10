#pragma once 
#include <vulkan/vulkan.hpp>
#include <unordered_map>

namespace RS {
	class ResourceManager;
	class RenderPassInfo {
	public:
		vk::Format colorFormat;
		vk::Format depthFormat;
		vk::SampleCountFlagBits samples;

		bool operator==(const RenderPassInfo& rhs) const;
	};
	struct RenderPassInfoHash {
		size_t operator()(const RenderPassInfo& k) const;
	};
	class RenderPassManager{
	private:
		ResourceManager& resourcemanager;
		std::unordered_map<RenderPassInfo, vk::RenderPass, RenderPassInfoHash> renderpasses;
	public:
		vk::RenderPass createRenderPass(const RenderPassInfo& info);
		vk::RenderPass getRenderPass(const RenderPassInfo& info);
		RenderPassManager(ResourceManager& resourcemanager);
		~RenderPassManager() = default;
		void destroy();
	};
}