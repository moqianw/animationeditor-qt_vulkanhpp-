#pragma once

#include <vulkan/vulkan.hpp>
#include "PipelineManager.hpp"
#include "ShaderManager.hpp"
#include "DescriptorSetManager.hpp"
#include "RenderPassManager.hpp"
#include "FrameBufferManager.hpp"
#include "MaterialManager.hpp"
#include "qobject.h"
namespace RS {
	class ResourceManager:public QObject{
		Q_OBJECT
	signals:
		void deviceready(const vk::Device& device);
	private:
		vk::Device device = nullptr;
		const uint32_t MAX_FRAMES_IN_FLIGHT = 2; // Ë«»º³å
	public:
		ResourceManager();
		ResourceManager& setDevice(const vk::Device& device);
		void destroy();
		~ResourceManager() = default;
		vk::Device getDevice() const { return device; }
		uint32_t getFramesInFlight() const { return MAX_FRAMES_IN_FLIGHT; }
		PipelineLayoutManager pipelinelayoutmanager;
		PipelineManager pipelinemanager;
		ShaderManager shadermanager;
		DescriptorSetManager descriptorsetmanager;
		RenderPassManager renderpassmanager;
		FrameBufferManager framebuffermanager;
		MaterialManager materialmanager;
	};
}