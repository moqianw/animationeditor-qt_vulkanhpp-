#pragma once

#include <vulkan/vulkan.hpp>
#include "qobject.h"
namespace RS {
	class Scene;
	class PipelineManager :public QObject{
		Q_OBJECT
	public:
		PipelineManager(Scene& scene);
		~PipelineManager();

		vk::Pipeline createGraphPipeline(
			const vk::RenderPass& renderpass,
			const vk::PipelineLayout& pipelinelayout,
			const std::vector<vk::PipelineShaderStageCreateInfo>& shaderstages);
		vk::PipelineLayout createPipelineLayout(
			const std::vector<vk::DescriptorSetLayout>& setlayouts,
			const std::vector<vk::PushConstantRange>& pushconstants);
		vk::Pipeline getPipeline(const uint32_t& index) {
			if (index >= pipelines.size()) return nullptr;
			return pipelines[index];
		}
		vk::PipelineLayout getPipelineLayout(const uint32_t& index) {
			if (index >= pipelinelayouts.size()) return nullptr;
			return pipelinelayouts[index];
		}
		void destroy();
	private:
		Scene& scene;
		std::vector<vk::Pipeline> pipelines;
		vk::PipelineCache pipelinecache = nullptr;
		std::vector<vk::PipelineLayout> pipelinelayouts;
	};
}