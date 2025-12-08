#pragma once

#include <vulkan/vulkan.hpp>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace RS {
	struct ShaderInfo {
		std::string path;
		vk::ShaderStageFlagBits flag;
		std::string entername;
		ShaderInfo& setPath(std::string path) {
			this->path = path;
			return*this;;
		}
		ShaderInfo& setShaderStageFlagBits(const vk::ShaderStageFlagBits& flag) {
			this->flag = flag;
			return *this;
		}
		ShaderInfo& setEnterName(std::string name) {
			this->entername = name;
			return *this;
		}
		ShaderInfo(std::string path, const vk::ShaderStageFlagBits& flag, std::string name)
			:path(path), flag(flag), entername(name)
		{

		}
		ShaderInfo(const ShaderInfo& other) :path(other.path), flag(other.flag), entername(other.entername) {

		}
		ShaderInfo& operator=(const ShaderInfo& other) {
			path = other.path;
			flag = other.flag;
			entername = other.entername;
			return *this;
		}
		bool operator==(const ShaderInfo& other) const {
			return path == other.path && flag == other.flag && entername == other.entername;
		}
	};
	struct ShaderInfoHash {
		size_t operator()(const ShaderInfo& k) const {
			size_t h1 = std::hash<std::string>()(k.path);
			size_t h2 = std::hash<uint32_t>()(static_cast<uint32_t>(k.flag));
			return h1 ^ (h2 << 1);
		}
	};

	class ShaderCreateInfo {

	public:
		ShaderCreateInfo& setShaderInfos(const std::vector<ShaderInfo>& shaderinfos) {
			this->shaderinfos = shaderinfos;
			return *this;
		}
	private:
		friend class ShaderManager;
		std::vector<ShaderInfo> shaderinfos;
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



	class Scene;
	class ShaderManager {
	private:
		Scene& scene;
		std::unordered_map<ShaderInfo, Shader, ShaderInfoHash> shaders;
	public:
		ShaderManager(Scene& scene );
		std::vector<Shader> loadShader(const ShaderCreateInfo& createinfo);
		void destroyShaders(const std::vector<ShaderInfo>& shaderinfos);


		void destroy() {
			//for (auto& [info, shader] : shaders) {
			//	scene.getDevice().destroyShaderModule(shader->shadersodule);
			//}
			
			shaders.clear();
		}
	};
}