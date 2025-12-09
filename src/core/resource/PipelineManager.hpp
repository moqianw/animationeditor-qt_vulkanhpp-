#pragma once

#include <vulkan/vulkan.hpp>
#include "RenderPassManager.hpp"
#include "ShaderManager.hpp"
#include "qobject.h"
#include "../utils/utils.hpp"
namespace RS {
	class ResourceManager;

	class PipelineLayoutInfo {
	public:
		struct DescriptorBindingInfo {
			uint32_t binding;
			vk::DescriptorType type;
			uint32_t count;
			vk::ShaderStageFlags stages;

			bool operator==(const DescriptorBindingInfo& k) const;
		};
		struct DescriptorSetLayoutInfo {
			uint32_t set;
			std::vector<DescriptorBindingInfo> bindings;

			bool operator==(const DescriptorSetLayoutInfo& k) const;
		};
		struct PushConstantInfo {
			vk::ShaderStageFlags stages;
			uint32_t offset;
			uint32_t size;

			bool operator==(const PushConstantInfo& k) const;
		};

		std::vector<DescriptorSetLayoutInfo> sets;
		std::vector<PushConstantInfo> pushConstants;

		bool operator==(const PipelineLayoutInfo& rhs) const;
	};
	struct PipelineLayoutInfoHash {
		size_t operator()(const PipelineLayoutInfo& k) const;
	};
	class PipelineLayoutManager {
	public:
		PipelineLayoutManager(ResourceManager& resourcemanager);
		vk::PipelineLayout createPipelineLayout(
			const PipelineLayoutInfo& layoutinfo);

		vk::PipelineLayout getPipelineLayout(
			const PipelineLayoutInfo& layoutinfo);
		void destroy();
	private:
		ResourceManager& resourcemanager;
		std::unordered_map<PipelineLayoutInfo, vk::PipelineLayout, PipelineLayoutInfoHash> pipelinelayouts;
	};


	class PipelineInfo {
	public:
		PipelineLayoutInfo pipelinelayout;
		RenderPassInfo renderPass;
		std::vector<ShaderInfo> shaderstages;
		// Fixed pipeline state
		vk::PrimitiveTopology topology;
		vk::PolygonMode polygonMode;
		vk::CullModeFlags cullMode;
		vk::FrontFace frontFace;

		bool depthTest;
		bool depthWrite;
		vk::CompareOp depthCompare;

		bool blendEnable;

		vk::BlendFactor srcColor;
		vk::BlendFactor dstColor;
		vk::BlendOp colorBlendOp;

		vk::BlendFactor srcAlpha;
		vk::BlendFactor dstAlpha;
		vk::BlendOp alphaBlendOp;
		bool operator==(const PipelineInfo& rhs) const;
	};
	struct PipelineInfoHash {
		size_t operator()(const PipelineInfo& k) const;
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
		PipelineManager(ResourceManager& resourcemanager);
		~PipelineManager();

		Pipeline createGraphPipeline(const PipelineInfo& pipelineinfo);
		Pipeline getGraphPipeline(const PipelineInfo& pipelineinfo);

		void destroy();
	private:
		ResourceManager& resourcemanager;
		PipelineLayoutManager& pipelinelayoutmanager;
		RenderPassManager& renderpassmanager;
		ShaderManager& shadermanager;
		std::unordered_map<PipelineInfo,Pipeline, PipelineInfoHash> pipelines;
		vk::PipelineCache pipelinecache = nullptr;
	};
}