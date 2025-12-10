#include "PipelineManager.hpp"
#include "ResourceManager.hpp"
#include "../utils/utils.hpp"
namespace RS {
	bool PipelineLayoutInfo::DescriptorBindingInfo::operator==(const DescriptorBindingInfo& k) const {
		return binding == k.binding &&
			type == k.type &&
			count == k.count &&
			stages == k.stages;
	}

	bool PipelineLayoutInfo::DescriptorSetLayoutInfo::operator==(const DescriptorSetLayoutInfo& k) const {
		return set == k.set &&
			bindings == k.bindings;
	}
	bool PipelineLayoutInfo::PushConstantInfo::operator==(const PushConstantInfo& k) const {
		return stages == k.stages &&
			offset == k.offset &&
			size == k.size;
	}
	bool PipelineLayoutInfo::operator==(const PipelineLayoutInfo& rhs) const {
		return sets == rhs.sets &&
			pushConstants == rhs.pushConstants;
	}
	size_t PipelineLayoutInfoHash::operator()(const PipelineLayoutInfo& k) const {
		size_t h = 0;
		for (auto& set : k.sets) {
			UT::hashCombine(h, set.set);
			for (auto& b : set.bindings) {
				UT::hashCombine(h, b.binding);
				UT::hashCombine(h, static_cast<VkDescriptorType>(b.type));
				UT::hashCombine(h, b.count);
				UT::hashCombine(h, static_cast<VkShaderStageFlags>(b.stages));
			}
		}
		for (auto& pc : k.pushConstants) {
			UT::hashCombine(h, static_cast<VkShaderStageFlags>(pc.stages));
			UT::hashCombine(h, pc.offset);
			UT::hashCombine(h, pc.size);
		}
		return h;
	}
	bool PipelineInfo::operator==(const PipelineInfo& rhs) const {
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
			colorBlendOp == rhs.colorBlendOp &&
			srcAlpha == rhs.srcAlpha &&
			dstAlpha == rhs.dstAlpha &&
			alphaBlendOp == rhs.alphaBlendOp;

	}
	size_t PipelineInfoHash::operator()(const PipelineInfo& k) const {
		size_t h = 0;
		UT::hashCombine(h, PipelineLayoutInfoHash{}(k.pipelinelayout));
		UT::hashCombine(h, RenderPassInfoHash{}(k.renderPass));
		for (auto& stage : k.shaderstages) {
			UT::hashCombine(h, ShaderInfoHash{}(stage));
		}
		////
		UT::hashCombine(h, static_cast<uint32_t>(k.topology));
		UT::hashCombine(h, static_cast<uint32_t>(k.polygonMode));
		UT::hashCombine(h, static_cast<uint32_t>(k.cullMode));
		UT::hashCombine(h, static_cast<uint32_t>(k.frontFace));

		UT::hashCombine(h, k.depthTest);
		UT::hashCombine(h, k.depthWrite);
		UT::hashCombine(h, static_cast<uint32_t>(k.depthCompare));

		UT::hashCombine(h, k.blendEnable);

		UT::hashCombine(h, static_cast<uint32_t>(k.srcColor));
		UT::hashCombine(h, static_cast<uint32_t>(k.dstColor));
		UT::hashCombine(h, static_cast<uint32_t>(k.colorBlendOp));

		UT::hashCombine(h, static_cast<uint32_t>(k.srcAlpha));
		UT::hashCombine(h, static_cast<uint32_t>(k.dstAlpha));
		UT::hashCombine(h, static_cast<uint32_t>(k.alphaBlendOp));

		return h;
	}
}
namespace RS{


	PipelineLayoutManager::PipelineLayoutManager(ResourceManager& resourcemanager) :resourcemanager(resourcemanager)
	{
	}

	vk::PipelineLayout PipelineLayoutManager::createPipelineLayout(
		const PipelineLayoutInfo& layoutinfo
	) {
		auto device = resourcemanager.getDevice();
		vk::PipelineLayoutCreateInfo createinfo;
		std::vector<vk::DescriptorSetLayout> setlayouts;
		for (auto& setinfo : layoutinfo.sets) {
			vk::DescriptorSetLayoutCreateInfo setcreateinfo;
			std::vector<vk::DescriptorSetLayoutBinding> bindings;
			for (auto& bindinginfo : setinfo.bindings) {
				vk::DescriptorSetLayoutBinding binding;
				binding.setBinding(bindinginfo.binding)
					.setDescriptorCount(bindinginfo.count)
					.setDescriptorType(bindinginfo.type)
					.setStageFlags(bindinginfo.stages);
				bindings.push_back(binding);
			}
			setcreateinfo.setBindings(bindings);
			auto setlayout = device.createDescriptorSetLayout(setcreateinfo);
			if (!setlayout) throw std::runtime_error("create descriptorsetlayout false");
			setlayouts.push_back(setlayout);
		}
		std::vector<vk::PushConstantRange> pushconstants;
		for (auto& pcinfo : layoutinfo.pushConstants) {
			vk::PushConstantRange pushconstant;
			pushconstant.setOffset(pcinfo.offset)
				.setSize(pcinfo.size)
				.setStageFlags(pcinfo.stages);
			pushconstants.push_back(pushconstant);
		}
		createinfo.setSetLayouts(setlayouts)
			.setPushConstantRanges(pushconstants);
		auto pipelinelayout = device.createPipelineLayout(createinfo);
		if (!pipelinelayout) throw std::runtime_error("create pipelinelayout false");
		this->setlayouts.insert({ layoutinfo, setlayouts });
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
	std::vector<vk::DescriptorSetLayout> PipelineLayoutManager::getDescriptorSetLayouts(const PipelineLayoutInfo& layoutinfo)
	{
		auto it = setlayouts.find(layoutinfo);
		if (it != setlayouts.end()) {
			return it->second;
		}
		else {
			getPipelineLayout(layoutinfo);
			return setlayouts[layoutinfo];
		}
	}
	void PipelineLayoutManager::destroy()
	{
		if (vk::Device device = resourcemanager.getDevice())
		{
			for (auto& [info, layout] : pipelinelayouts) {
				if (layout) device.destroyPipelineLayout(layout);
			}
		}
		pipelinelayouts.clear();
	}


	PipelineManager::PipelineManager(ResourceManager& resourcemanager) :
		resourcemanager(resourcemanager),	
		pipelinelayoutmanager(resourcemanager.pipelinelayoutmanager),
		renderpassmanager(resourcemanager.renderpassmanager),
		shadermanager(resourcemanager.shadermanager)
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
		auto shaders = shadermanager.getShaders(pipelineinfo.shaderstages);
		auto shaderstages = shadermanager.getPipelineShaderStageCreateInfos(pipelineinfo.shaderstages);
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
			.setTopology(pipelineinfo.topology);

		//viewport
		vk::PipelineViewportStateCreateInfo viewport;

		viewport.setViewports({ })
			.setScissors({ })
			.setViewportCount(1)
			.setScissorCount(1);

		//光栅化

		vk::PipelineRasterizationStateCreateInfo rasterizationstate;
		rasterizationstate.setCullMode(pipelineinfo.cullMode)
			.setRasterizerDiscardEnable(false)
			.setFrontFace(pipelineinfo.frontFace)
			.setLineWidth(1)
			.setPolygonMode(pipelineinfo.polygonMode);

		//多重采样
		vk::PipelineMultisampleStateCreateInfo multisamplestate;
		multisamplestate.setSampleShadingEnable(false)
			.setRasterizationSamples(vk::SampleCountFlagBits::e1);

		//深度测试
		vk::PipelineDepthStencilStateCreateInfo depthstencilstate;
		depthstencilstate.setDepthTestEnable(pipelineinfo.depthTest)
			.setDepthWriteEnable(pipelineinfo.depthWrite)
			.setDepthCompareOp(pipelineinfo.depthCompare)
			.setDepthBoundsTestEnable(false)
			.setStencilTestEnable(false);

		//颜色混合

		vk::PipelineColorBlendStateCreateInfo colorblendstate;
		vk::PipelineColorBlendAttachmentState attachment;
		attachment.setBlendEnable(pipelineinfo.blendEnable)
			.setAlphaBlendOp(pipelineinfo.alphaBlendOp)
			.setColorBlendOp(pipelineinfo.colorBlendOp)
			.setColorWriteMask(vk::ColorComponentFlagBits::eA
				| vk::ColorComponentFlagBits::eR
				| vk::ColorComponentFlagBits::eG
				| vk::ColorComponentFlagBits::eB)
			.setDstAlphaBlendFactor(pipelineinfo.dstAlpha)
			.setSrcAlphaBlendFactor(pipelineinfo.srcAlpha)
			.setDstColorBlendFactor(pipelineinfo.dstColor)
			.setSrcColorBlendFactor(pipelineinfo.srcColor);
		colorblendstate.setAttachments({ attachment })
			.setLogicOpEnable(false);

		//dynamicstate
		vk::PipelineDynamicStateCreateInfo dynamicstate;
		std::vector<vk::DynamicState> dynamicstates = { vk::DynamicState::eViewport,vk::DynamicState::eScissor };
		dynamicstate.setDynamicStates(dynamicstates);
		auto pipelinelayout = pipelinelayoutmanager.getPipelineLayout(pipelineinfo.pipelinelayout);
		auto renderpass = renderpassmanager.getRenderPass(pipelineinfo.renderPass);

		createinfo.setPVertexInputState(&vertexinputstate)
			.setStages(shaderstages)
			.setPInputAssemblyState(&inputassembly)
			.setPViewportState(&viewport)
			.setPDynamicState(&dynamicstate)
			.setPRasterizationState(&rasterizationstate)
			.setPMultisampleState(&multisamplestate)
			.setPDepthStencilState(&depthstencilstate)
			.setPColorBlendState(&colorblendstate)
			.setLayout(pipelinelayout) // pipelinelayout
			.setRenderPass(renderpass); // renderpass
		auto device = resourcemanager.getDevice();
		auto result = device.createGraphicsPipeline(pipelinecache, createinfo);
		if (result.result != vk::Result::eSuccess) throw std::runtime_error("create grapics pipeline false");
		if (!result.value) {
			throw std::runtime_error("Pipeline is null, check shader interface, render pass, or vertex layout");
		}
		auto graphicepipeline = result.value;
		auto pipeline = std::make_shared<Pipeline_>();
		pipeline->pipeline = graphicepipeline;
		pipeline->pipelinelayout = pipelinelayout;

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

	




}