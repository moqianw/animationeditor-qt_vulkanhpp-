#pragma once

#include <vulkan/vulkan.hpp>
#include "ShaderManager.hpp"
#include "RenderPassManager.hpp"
#include "PipelineManager.hpp"
#include <string>
namespace RS {
	class ResourceManager;
	class MaterialInfo {
	public:
		std::string name;
		PipelineLayoutInfo layoutinfo;
		PipelineInfo pipelineinfo;
		RenderPassInfo renderpassinfo;
		MaterialInfo operator=(const MaterialInfo& other) = default;
	};
	class Material_{
	public:
	private:
		friend class MaterialManager;
		std::string name;
		Pipeline pipeline;
		vk::DescriptorSet persistentDescriptorSet;
		std::vector<vk::DescriptorSet> frameDescriptorSets;

	};
	using Material = std::shared_ptr<Material_>;
	class MaterialLoader {
	public:
		MaterialInfo loadFromFile(const std::string& path);
	};
	class MaterialManager {
	public:
		MaterialManager(ResourceManager& resourcemanager);
		~MaterialManager() = default;
		Material createMaterial(const MaterialInfo& materialinfo);
		void destroy();
	private:
		ResourceManager& resourcemanager;

	};
}