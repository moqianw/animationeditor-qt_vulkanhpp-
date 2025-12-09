#pragma once

#include <vulkan/vulkan.hpp>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "../utils/utils.hpp"
namespace RS {
	struct ShaderInfo {
		std::string path;
		vk::ShaderStageFlagBits flag;
		std::string entername;

		ShaderInfo& operator=(const ShaderInfo& other) = default;
		bool operator==(const ShaderInfo& other) const {
			return path == other.path && flag == other.flag && entername == other.entername;
		}
	};
	struct ShaderInfoHash {
		size_t operator()(const ShaderInfo& k) const;
	};

	class Shader_;
	using Shader = std::shared_ptr<Shader_>;

	class Shader_ {
	private:
		friend class ShaderManager;
		std::string path;
		vk::ShaderStageFlagBits flag;
		std::string entername;
		vk::ShaderModule shadersodule = nullptr;
	public:
		std::string getPath() const { return path; }
		vk::ShaderStageFlagBits getFlag() const { return flag; }
		Shader_() = default;
		~Shader_() = default;
		Shader_(const Shader_& other) = default;
		Shader_& operator=(const Shader_& other) = default;
		operator bool() const {
			return shadersodule != nullptr;
		}
	private:

	};



	class ResourceManager;
	class ShaderManager {
	private:
		ResourceManager& resourcemanager;
		std::unordered_map<ShaderInfo, Shader, ShaderInfoHash> shaders;
	public:
		ShaderManager(ResourceManager& resourcemanager);
		std::vector<Shader> loadShader(const std::vector<ShaderInfo>& createinfo);
		std::vector<Shader> getShaders(const std::vector<ShaderInfo>& createinfo);
		std::vector<vk::PipelineShaderStageCreateInfo> getPipelineShaderStageCreateInfos(const std::vector<ShaderInfo>& shaderinfos);
		void destroyShaders(const std::vector<ShaderInfo>& shaderinfos);


		void destroy();
	};
}