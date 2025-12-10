#pragma once

#include <vulkan/vulkan.hpp>
#include "qobject.h"

namespace RS {

	class DescriptorPool_ {
	public:

		DescriptorPool_() = default;
		~DescriptorPool_() = default;
		std::vector<vk::DescriptorSet> allocateDescriptorSets(const std::vector<vk::DescriptorSetLayout>& layouts);
		void reset();
		DescriptorPool_(const DescriptorPool_& other) = delete;
		DescriptorPool_& operator=(const DescriptorPool_& other) = delete;

		operator bool() {
			return descriptorpool;
		}
		bool operator!() {
			return !descriptorpool;
		}
		void destroy();
	private:
		friend class DescriptorSetManager;

		vk::Device device = nullptr;
		vk::DescriptorPool descriptorpool;
		std::vector<vk::DescriptorSet> descriptorsets;

	};
	using DescriptorPool = std::shared_ptr<DescriptorPool_>;


	enum class DescriptorPoolSizeFlag {
		eGeneral,
		eShadow,
		eCompute,
		eTiny
	};
	enum class DescriptorLifetimeFlag {
		ePersistent,   // 长期存在（material、texture）
		ePerFrame      // 每帧 reset（camera、frame ubo）
	};
	class DescriptorSetAllocateInfo {
	public:
		DescriptorSetAllocateInfo& setDescriptorSetLayouts(const std::vector<vk::DescriptorSetLayout>& layouts) {
			this->layouts = layouts;
			return *this;
		}
		DescriptorSetAllocateInfo& setDescriptorPoolCreateFlags(const vk::DescriptorPoolCreateFlags& poolflags) {
			this->poolflags = poolflags;
			return *this;
		}	
		DescriptorSetAllocateInfo& setDescriptorPoolSizeFlags(const DescriptorPoolSizeFlag& poolsizetype) {
			this->poolsizetype = poolsizetype;
			return *this;
		}
		DescriptorSetAllocateInfo& setDescriptorLifetimeFlags(const DescriptorLifetimeFlag& lifetimetype) {
			this->lifetimetype = lifetimetype;
			return *this;
		}
		DescriptorSetAllocateInfo& setFrameIndex(const uint32_t& frameindex) {
			this->frameindex = frameindex;
			return *this;
		}
		std::vector<vk::DescriptorSetLayout> layouts;
		vk::DescriptorPoolCreateFlags poolflags;
		DescriptorPoolSizeFlag poolsizetype;
		DescriptorLifetimeFlag lifetimetype;
		uint32_t frameindex = 0;
	};
	class ResourceManager;

	class DescriptorSetManager:public QObject {
		Q_OBJECT
	public:
		DescriptorSetManager(ResourceManager& resourcemanager);
		void init();
		void destroy();

		std::vector<vk::DescriptorSet> allocateDescriptorSet(const DescriptorSetAllocateInfo& allocateinfo);
		void resetFramePools(const uint32_t& frameindex);
	private:
		ResourceManager& resourcemanager;
		DescriptorPool createDescriptorPool(
			const DescriptorPoolSizeFlag& poolsizeflag, const vk::DescriptorPoolCreateFlags& flag);


		std::vector<vk::DescriptorPoolSize> generalpoolSizes;
		std::vector<vk::DescriptorPoolSize> shadowpoolSizes;
		std::vector<vk::DescriptorPoolSize> computepoolSizes;
		std::vector<vk::DescriptorPoolSize> tinypoolSizes;

		std::vector<DescriptorPool> contpools;
		std::vector<std::vector<DescriptorPool>> framepools;
	};
}