#pragma once

#include <vulkan/vulkan.hpp>
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

			bool operator==(const DescriptorBindingInfo& k) const {
				return binding == k.binding &&
					type == k.type &&
					count == k.count &&
					stages == k.stages;
			}
		};
		struct DescriptorSetLayoutInfo {
			uint32_t set;
			std::vector<DescriptorBindingInfo> bindings;

			bool operator==(const DescriptorSetLayoutInfo& k) const  {
				return set == k.set &&
					bindings == k.bindings;
			}
		};
		struct PushConstantInfo {
			vk::ShaderStageFlags stages;
			uint32_t offset;
			uint32_t size;

			bool operator==(const PushConstantInfo& k) const {
				return stages == k.stages &&
					offset == k.offset &&
					size == k.size;
			}
		};

		std::vector<DescriptorSetLayoutInfo> sets;
		std::vector<PushConstantInfo> pushConstants;

		bool operator==(const PipelineLayoutInfo& rhs) const {
			return sets == rhs.sets &&
				pushConstants == rhs.pushConstants;
		}
	};
	struct PipelineLayoutInfoHash {
		size_t operator()(const PipelineLayoutInfo& k) const {
			size_t h = 0;
			for (auto& set : k.sets) {
				UT::hashCombine(h, set.set);
				for (auto& b : set.bindings) {
					UT::hashCombine(h, b.binding);
					UT::hashCombine(h, static_cast<VkDescriptorType>(b.type));
					UT::hashCombine(h, b.count);
					UT::hashCombine(h, static_cast<VkShaderStageFlags>( b.stages));
				}
			}
			for (auto& pc : k.pushConstants) {
				UT::hashCombine(h, static_cast<VkShaderStageFlags>(pc.stages));
				UT::hashCombine(h, pc.offset);
				UT::hashCombine(h, pc.size);
			}
			return h;
		}
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




	class RenderPassInfo;
	class PipelineInfo {
	public:
		PipelineLayoutInfo pipelinelayout;
		RenderPassInfo renderPass;
		std::vector<vk::PipelineShaderStageCreateInfo> shaderstages;
		// Fixed pipeline state
		VkPrimitiveTopology topology;
		VkPolygonMode polygonMode;
		VkCullModeFlags cullMode;
		VkFrontFace frontFace;

		bool depthTest;
		bool depthWrite;
		VkCompareOp depthCompare;

		bool blendEnable;
		VkBlendFactor srcColor;
		VkBlendFactor dstColor;
		VkBlendOp blendOp;
		bool operator==(const PipelineInfo& rhs) const {
			return pipelinelayout == rhs.pipelinelayout &&
				renderPass == rhs.renderPass &&
				shaderstages == rhs.shaderstages &&
				topology == rhs.topology &&
				polygonMode == rhs.polygonMode &&
				cullMode == rhs.cullMode &&
				frontFace == rhs.frontFace &&
				depthTest == rhs.depthTest &&
				depthWrite == rhs.depthWrite &&
				depthCompare == rhs.depthCompare &&
				blendEnable == rhs.blendEnable &&
				srcColor == rhs.srcColor &&
				dstColor == rhs.dstColor &&
				blendOp == rhs.blendOp;
		}
	};
	struct PipelineInfoHash {
		size_t operator()(const PipelineInfo& k) const {
			size_t h = 0;
			UT::hashCombine(h, static_cast<size_t>(PipelineLayoutInfoHash{}(k.pipelinelayout)));
			UT::hashCombine(h, k.renderPassKey);

			UT::hashCombine(h, k.topology);
			UT::hashCombine(h, k.polygonMode);
			UT::hashCombine(h, k.cullMode);
			UT::hashCombine(h, k.frontFace);

			UT::hashCombine(h, k.depthTestEnable);
			UT::hashCombine(h, k.depthWriteEnable);
			UT::hashCombine(h, k.depthCompareOp);

			UT::hashCombine(h, k.blendEnable);
			UT::hashCombine(h, k.srcColorBlend);
			UT::hashCombine(h, k.dstColorBlend);
			UT::hashCombine(h, k.colorBlendOp);

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
		PipelineManager(ResourceManager& resourcemanager);
		~PipelineManager();

		Pipeline createGraphPipeline(const PipelineInfo& pipelineinfo);
		Pipeline getGraphPipeline(const PipelineInfo& pipelineinfo);

		void destroy();
	private:
		ResourceManager& resourcemanager;
		PipelineLayoutManager& pipelinelayoutmanager;
		std::unordered_map<PipelineInfo,Pipeline, PipelineInfoHash> pipelines;
		vk::PipelineCache pipelinecache = nullptr;
	};
}