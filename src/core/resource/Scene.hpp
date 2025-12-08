#pragma once
#include <vulkan/vulkan.hpp>
#include "PipelineManager.hpp"
#include "ShaderManager.hpp"
#include "DescriptorSetManager.hpp"
#include "qobject.h"
namespace RS {
	class Scene:public QObject{
		Q_OBJECT
	signals:
		void deviceready(const vk::Device& device);
	private:
		vk::Device device = nullptr;
	public:
		Scene();
		Scene& setDevice(const vk::Device& device);
		void destroy();
		~Scene() = default;
		vk::Device getDevice() const { return device; }
		PipelineLayoutManager pipelinelayoutmanager;
		PipelineManager pipelinemanager;
		ShaderManager shadermanager;
		DescriptorSetManager descriptorsetmanager;
	};
}