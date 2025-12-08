#pragma once

#include <vulkan/vulkan.hpp>
#include "qobject.h"
#include "../utils/utils.hpp"
namespace RS {
	class Scene;

	class PipelineLayoutInfo {
	public:
		std::vector<vk::DescriptorSetLayout> setLayouts;
		std::vector<vk::PushConstantRange> pushConstants;

		bool operator==(const PipelineLayoutInfo& rhs) const {
			return setLayouts == rhs.setLayouts &&
				std::equal(pushConstants.begin(), pushConstants.end(),
					rhs.pushConstants.begin(),
					[](auto& a, auto& b) {
						return a.stageFlags == b.stageFlags &&
							a.offset == b.offset &&
							a.size == b.size;
					});
		}
	};
	struct PipelineLayoutInfoHash {
		size_t operator()(const PipelineLayoutInfo& k) const {
			size_t h = 0;

			for (auto layout : k.setLayouts) {
				UT::hashCombine(h, reinterpret_cast<uint64_t>(static_cast<VkDescriptorSetLayout>(layout)));
			}

			for (auto& pc : k.pushConstants) {
				UT::hashCombine(h, static_cast<uint32_t>(pc.stageFlags));
				UT::hashCombine(h, pc.offset);
				UT::hashCombine(h, pc.size);
			}

			return h;
		}
	};
	class PipelineLayoutManager {
	public:
		PipelineLayoutManager(Scene& scene);
		vk::PipelineLayout createPipelineLayout(
			const std::vector<vk::DescriptorSetLayout>& setlayouts,
			const std::vector<vk::PushConstantRange>& pushconstants);
		void destroy();
	private:
		Scene& scene;
		std::unordered_map<PipelineLayoutInfo, vk::PipelineLayout, PipelineLayoutInfoHash> pipelinelayouts;
	};





	class PipelineInfo {
	public:

	};
	struct PipelineInfoHash {
		size_t operator()(const PipelineInfo& k) const {
			size_t h = 0;
			return h;
		}
	};
	class Pipeline_ {
	public:

	private:
		friend class PipelineManager;
		vk::Pipeline pipeline = nullptr;
		vk::PipelineLayout pipelinelayout = nullptr;
	};
	using Pipeline = std::shared_ptr<Pipeline_>;


	class PipelineManager :public QObject{
		Q_OBJECT
	public:
		PipelineManager(Scene& scene);
		~PipelineManager();

		vk::Pipeline createGraphPipeline(
			const vk::RenderPass& renderpass,
			const vk::PipelineLayout& pipelinelayout,
			const std::vector<vk::PipelineShaderStageCreateInfo>& shaderstages);

		void destroy();
	private:
		Scene& scene;
		PipelineLayoutManager& pipelinelayoutmanager;
		std::unordered_map<PipelineInfo,Pipeline, PipelineInfoHash> pipelines;
		vk::PipelineCache pipelinecache = nullptr;
	};
}