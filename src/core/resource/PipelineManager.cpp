#include "PipelineManager.hpp"
#include "../utils/utils.hpp"
#include "ResourceManager.hpp"
namespace RS {


	PipelineManager::PipelineManager(ResourceManager& resourcemanager) :resourcemanager(resourcemanager), pipelinelayoutmanager(resourcemanager.pipelinelayoutmanager)
	{
		connect(&resourcemanager, &ResourceManager::deviceready, this, [this](const vk::Device& device) {
			vk::PipelineCacheCreateInfo cacheinfo;
			pipelinecache = device.createPipelineCache(cacheinfo);
			}, Qt::SingleShotConnection);

	}
	PipelineManager::~PipelineManager()
	{
		destroy();
	}
	void PipelineManager::destroy() {
		if (vk::Device device = resourcemanager.getDevice()) {
			for (auto& [info,pipeline] : pipelines) {
				if (pipeline->pipeline) device.destroyPipeline(pipeline->pipeline);
			}
			pipelines.clear();
			if (pipelinecache) device.destroyPipelineCache(pipelinecache);
			pipelinecache = nullptr;
		}

	}

	Pipeline PipelineManager::createGraphPipeline(const PipelineInfo& pipelineinfo) {

		vk::GraphicsPipelineCreateInfo createinfo;
		//着色器

		//顶点输入
		vk::PipelineVertexInputStateCreateInfo vertexinputstate;
		std::vector<vk::VertexInputBindingDescription> vertexbindings = { UT::Vertex4::getVertexInputBindingDescription(0) };
		auto vertexattribute = UT::Vertex4::getVertexInputAttributeDescription(0);
		vertexinputstate.setVertexBindingDescriptions(vertexbindings)
			.setVertexAttributeDescriptions(vertexattribute);

		///顶点聚集
		vk::PipelineInputAssemblyStateCreateInfo inputassembly;

		inputassembly
			.setPrimitiveRestartEnable(false)
			.setTopology(vk::PrimitiveTopology::eTriangleList);

		//viewport
		vk::PipelineViewportStateCreateInfo viewport;

		viewport.setViewports({ })
			.setScissors({ })
			.setViewportCount(1)
			.setScissorCount(1);

		//光栅化
		vk::PipelineRasterizationStateCreateInfo rasterizationstate;
		rasterizationstate.setCullMode(vk::CullModeFlagBits::eBack)
			.setRasterizerDiscardEnable(false)
			.setFrontFace(vk::FrontFace::eCounterClockwise)
			.setLineWidth(1)
			.setPolygonMode(vk::PolygonMode::eFill);

		//多重采样
		vk::PipelineMultisampleStateCreateInfo multisamplestate;
		multisamplestate.setSampleShadingEnable(false)
			.setRasterizationSamples(vk::SampleCountFlagBits::e1);

		//深度测试
		vk::PipelineDepthStencilStateCreateInfo depthstencilstate;
		depthstencilstate.setDepthTestEnable(true)
			.setDepthWriteEnable(true)
			.setDepthCompareOp(vk::CompareOp::eLess)
			.setDepthBoundsTestEnable(false)
			.setStencilTestEnable(false);

		//颜色混合

		vk::PipelineColorBlendStateCreateInfo colorblendstate;
		vk::PipelineColorBlendAttachmentState attachment;
		attachment.setBlendEnable(true)
			.setAlphaBlendOp(vk::BlendOp::eAdd)
			.setColorBlendOp(vk::BlendOp::eAdd)
			.setColorWriteMask(vk::ColorComponentFlagBits::eA
				| vk::ColorComponentFlagBits::eR
				| vk::ColorComponentFlagBits::eG
				| vk::ColorComponentFlagBits::eB)
			.setDstAlphaBlendFactor(vk::BlendFactor::eZero)
			.setSrcAlphaBlendFactor(vk::BlendFactor::eOne)
			.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
			.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha);
		colorblendstate.setAttachments({ attachment })
			.setLogicOpEnable(false);

		//dynamicstate
		vk::PipelineDynamicStateCreateInfo dynamicstate;
		std::vector<vk::DynamicState> dynamicstates = { vk::DynamicState::eViewport,vk::DynamicState::eScissor };
		dynamicstate.setDynamicStates(dynamicstates);

		if (!pipelineinfo.pipelinelayout) throw std::runtime_error("not create pipelinelayout");
		if (!pipelineinfo.renderPass) throw std::runtime_error("not create renderpass");
		createinfo.setPVertexInputState(&vertexinputstate)
			.setStages(pipelineinfo.shaderstages)
			.setPInputAssemblyState(&inputassembly)
			.setPViewportState(&viewport)
			.setPDynamicState(&dynamicstate)
			.setPRasterizationState(&rasterizationstate)
			.setPMultisampleState(&multisamplestate)
			.setPDepthStencilState(&depthstencilstate)
			.setPColorBlendState(&colorblendstate)
			.setLayout(pipelineinfo.pipelinelayout) // pipelinelayout
			.setRenderPass(pipelineinfo.renderPass); // renderpass
		auto device = resourcemanager.getDevice();
		auto result = device.createGraphicsPipeline(pipelinecache, createinfo);
		if (result.result != vk::Result::eSuccess) throw std::runtime_error("create grapics pipeline false");
		if (!result.value) {
			throw std::runtime_error("Pipeline is null, check shader interface, render pass, or vertex layout");
		}
		auto graphicepipeline = result.value;
		auto pipeline = std::make_shared<Pipeline_>();
		pipeline->pipeline = graphicepipeline;
		pipeline->pipelinelayout = pipelineinfo.pipelinelayout;
		pipelines.insert({ pipelineinfo, pipeline });
		return pipeline;
	}

	Pipeline PipelineManager::getGraphPipeline(const PipelineInfo& pipelineinfo)
	{
		auto pipeline = pipelines.find(pipelineinfo);
		if (pipeline != pipelines.end()) {
			return pipeline->second;
		}
		else
		{
			return createGraphPipeline(pipelineinfo);
		}
	}

	PipelineLayoutManager::PipelineLayoutManager(ResourceManager& resourcemanager) :resourcemanager(resourcemanager)
	{
	}

	vk::PipelineLayout PipelineLayoutManager::createPipelineLayout(
		const PipelineLayoutInfo& layoutinfo
	) {
		auto device = resourcemanager.getDevice();
		vk::PipelineLayoutCreateInfo createinfo;
		createinfo.setSetLayouts(layoutinfo.setLayouts)
			.setPushConstantRanges(layoutinfo.pushConstants);
		auto pipelinelayout = device.createPipelineLayout(createinfo);
		if (!pipelinelayout) throw std::runtime_error("create pipelinelayout false");

		pipelinelayouts.insert({ layoutinfo, pipelinelayout });
		return pipelinelayout;
	}
	vk::PipelineLayout PipelineLayoutManager::getPipelineLayout(
		const PipelineLayoutInfo& layoutinfo
	) {
		auto device = resourcemanager.getDevice();
		auto layout = pipelinelayouts.find(layoutinfo);
		if (layout != pipelinelayouts.end()) {
			return layout->second;
		}
		else {
			return createPipelineLayout(layoutinfo);
		}
	}
	void PipelineLayoutManager::destroy()
	{
		if (vk::Device device = resourcemanager.getDevice())
		{
			for (auto& [info,layout] : pipelinelayouts) {
				if (layout) device.destroyPipelineLayout(layout);
			}
		}
		pipelinelayouts.clear();
	}

}