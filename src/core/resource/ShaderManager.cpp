#include "ShaderManager.hpp"
#include "../utils/utils.hpp"
#include "Scene.hpp"
namespace RS {
	ShaderManager::ShaderManager(Scene& scene) : scene(scene)
	{
	}
	std::vector<Shader> ShaderManager::loadShader(const ShaderCreateInfo& createinfo) {
		std::vector<Shader> sh;
		for (auto& info : createinfo.shaderinfos) {
			auto module = UT::ShaderStagesCreater::createShaderModule(scene.getDevice(), UT::FileReader::read(info.path));
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
	void ShaderManager::destroyShaders(const std::vector<ShaderInfo>& shaderinfos)
	{
		for (auto& info : shaderinfos) {
			shaders.erase(info);
		}
	}

}