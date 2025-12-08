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
		void free(const std::vector<vk::DescriptorSet>& setsToFree);
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


	enum class DescriptorPoolSizeFlagBits {
		eGeneral,
		eShadow,
		eCompute,
		eTiny
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
		DescriptorSetAllocateInfo& setDescriptorPoolSizeFlags(const DescriptorPoolSizeFlagBits& poolsizetype) {
			this->poolsizetype = poolsizetype;
			return *this;
		}
		std::vector<vk::DescriptorSetLayout> layouts;
		vk::DescriptorPoolCreateFlags poolflags;
		DescriptorPoolSizeFlagBits poolsizetype;
	};
	class Scene;
	class DescriptorSetManager:public QObject {
		Q_OBJECT
	public:
		DescriptorSetManager(Scene& scene);
		void init();
		void destroy();

		// 核心分配接口
		std::vector<vk::DescriptorSet> allocateDescriptorSet(const DescriptorSetAllocateInfo& allocateinfo);

	private:
		Scene& scene;
		DescriptorPool createDescriptorPool(
			const DescriptorPoolSizeFlagBits& poolsizeflag, const vk::DescriptorPoolCreateFlags& flag);


		std::vector<vk::DescriptorPoolSize> generalpoolSizes;
		std::vector<vk::DescriptorPoolSize> shadowpoolSizes;
		std::vector<vk::DescriptorPoolSize> computepoolSizes;
		std::vector<vk::DescriptorPoolSize> tinypoolSizes;

		std::vector<DescriptorPool> contpools;
		std::vector<DescriptorPool> framepools;
	};
}