#pragma once 
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include "../utils/utils.hpp"
namespace RS {
	class ResourceManager;
	class RenderPassInfo {
	public:
		vk::Format colorFormat;
		vk::Format depthFormat;
		vk::SampleCountFlagBits samples;

		bool operator==(const RenderPassInfo& rhs) const {
			return colorFormat == rhs.colorFormat&&
				depthFormat == rhs.depthFormat &&
				samples == rhs.samples;
		}
	};
	struct RenderPassInfoHash {
		size_t operator()(const RenderPassInfo& k) const {
			size_t h = 0;
			UT::hashCombine(h, static_cast<uint32_t>(k.colorFormat));
			UT::hashCombine(h, static_cast<uint32_t>(k.depthFormat));
			UT::hashCombine(h, static_cast<uint32_t>(k.samples));
			return h;
		}
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