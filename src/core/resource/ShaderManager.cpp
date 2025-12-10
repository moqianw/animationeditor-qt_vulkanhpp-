#include "ShaderManager.hpp"


#include "ResourceManager.hpp"
#include "../utils/utils.hpp"

namespace RS {
	size_t ShaderInfoHash::operator()(const ShaderInfo& k) const {

		size_t h1 = std::hash<std::string>()(k.path);
		size_t h2 = std::hash<uint32_t>()(static_cast<uint32_t>(k.flag));
		UT::hashCombine(h2, h1);
		return h2;
	}


	ShaderManager::ShaderManager(ResourceManager& resourcemanager) : resourcemanager(resourcemanager)
	{
	}
	std::vector<Shader> ShaderManager::loadShader(const std::vector<ShaderInfo>& createinfo) {
		std::vector<Shader> sh;
		for (auto& info : createinfo) {
			auto module = UT::ShaderStagesCreater::createShaderModule(resourcemanager.getDevice(), UT::FileReader::read(info.path));
			Shader shader;
			shader->entername = info.entername;
			shader->flag = info.flag;
			shader->path = info.path;
			shader->shadersodule = module.value();
			shaders.insert( { info, shader });
			sh.push_back(Shader());
		}

		return sh;
	}
	std::vector<Shader> ShaderManager::getShaders(const std::vector<ShaderInfo>& createinfo)
	{
		std::vector<Shader> sh;
		std::vector<ShaderInfo> toload;
		for (auto& info : createinfo) {
			auto shader = shaders.find(info);
			if (shader == shaders.end()) {			
				toload.push_back(info);
			}
			else
			{
				sh.push_back(shader->second);
			}
		}
		auto loadedshaders = loadShader(toload);
		sh.insert(sh.end(), loadedshaders.begin(), loadedshaders.end());
		return sh;
	}
	std::vector<vk::PipelineShaderStageCreateInfo> ShaderManager::getPipelineShaderStageCreateInfos(const std::vector<ShaderInfo>& shaderinfos)
	{
		std::vector<vk::PipelineShaderStageCreateInfo> stages;
		for (auto& info : shaderinfos) {
			auto shader = shaders.find(info);
			if (shader == shaders.end()) {
				throw std::runtime_error("shader not found in ShaderManager!");
			}
			vk::PipelineShaderStageCreateInfo stage;
			stage.setModule(shader->second->shadersodule)
				.setStage(shader->second->flag)
				.setPName(shader->second->entername.c_str());
			stages.push_back(stage);
		}
		return stages;
	}
	void ShaderManager::destroyShaders(const std::vector<ShaderInfo>& shaderinfos)
	{
		for (auto& info : shaderinfos) {
			shaders.erase(info);
		}
	}

	void ShaderManager::destroy()
	{
		for(auto& [info, shader] : shaders) {
			resourcemanager.getDevice().destroyShaderModule(shader->shadersodule);
		}
		shaders.clear();
	}

}