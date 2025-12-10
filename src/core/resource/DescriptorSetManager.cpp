#include "DescriptorSetManager.hpp"
#include "ResourceManager.hpp"
#include <algorithm>
namespace RS {
	void DescriptorPool_::destroy() {
		if (device && descriptorpool) device.destroyDescriptorPool(descriptorpool);
		descriptorsets = {};
		device = nullptr;
		descriptorpool = nullptr;
	}
	std::vector<vk::DescriptorSet> DescriptorPool_::allocateDescriptorSets(const std::vector<vk::DescriptorSetLayout>& layouts) {
		vk::DescriptorSetAllocateInfo allocateinfo;
		allocateinfo.setDescriptorPool(descriptorpool)
			.setDescriptorSetCount(static_cast<uint32_t>(layouts.size()))
			.setSetLayouts(layouts);

		auto sets = device.allocateDescriptorSets(allocateinfo);

		descriptorsets.insert(descriptorsets.end(), sets.begin(), sets.end());
		return sets;
	}
	void DescriptorPool_::reset() {
		device.resetDescriptorPool(descriptorpool);
		descriptorsets.clear();
	}
	std::vector<vk::DescriptorSet> DescriptorSetManager::allocateDescriptorSet(
		const DescriptorSetAllocateInfo& info)
	{
		if (info.layouts.empty()) {
			throw std::runtime_error(
				"DescriptorSetManager::allocateDescriptorSet: empty layouts"
			);
		}

		std::vector<DescriptorPool>* pools = nullptr;

		if (info.lifetimetype == DescriptorLifetimeFlag::ePersistent) {
			pools = &contpools;
		}
		else {
			pools = &framepools[info.frameindex];
		}

		for (auto it = pools->rbegin(); it != pools->rend(); ++it) {
			try {
				return (*it)->allocateDescriptorSets(info.layouts);
			}
			catch (const vk::OutOfPoolMemoryError&) {
			}
		}
		DescriptorPool pool =
			createDescriptorPool(info.poolsizetype, info.poolflags);

		auto sets = pool->allocateDescriptorSets(info.layouts);
		pools->push_back(pool);

		return sets;

	}
	void DescriptorSetManager::resetFramePools(const uint32_t& frameindex)
	{
		if (frameindex >= framepools.size()) {
			return;
		}
		for (auto& computepoolSizes : framepools[frameindex]) {
			computepoolSizes->reset();
		}
	}
	DescriptorPool DescriptorSetManager::createDescriptorPool(const DescriptorPoolSizeFlag& poolsizeflag, const vk::DescriptorPoolCreateFlags& flag)
	{
		vk::DescriptorPoolCreateInfo poolcreateinfo;
		
		poolcreateinfo.setFlags(flag);
		switch (poolsizeflag)
		{
		case DescriptorPoolSizeFlag::eGeneral:
			poolcreateinfo.setMaxSets(512)
				.setPoolSizes(generalpoolSizes);
			break;
		case DescriptorPoolSizeFlag::eShadow:
			poolcreateinfo.setMaxSets(256)
				.setPoolSizes(shadowpoolSizes);
			break;

		case DescriptorPoolSizeFlag::eCompute:
			poolcreateinfo.setMaxSets(256)
				.setPoolSizes(computepoolSizes);
			break;
		case DescriptorPoolSizeFlag::eTiny:
			poolcreateinfo.setMaxSets(64)
				.setPoolSizes(tinypoolSizes);
			break;
		default:
			throw std::runtime_error("create DescriptorPool ERROR: false PoolSizeFlag");
			break;
		}
		DescriptorPool pool = std::make_shared<DescriptorPool_>();
		pool->descriptorpool = resourcemanager.getDevice().createDescriptorPool(poolcreateinfo);
		pool->device = resourcemanager.getDevice();
		return pool;
	}
	DescriptorSetManager::DescriptorSetManager(ResourceManager& resourcemanager):resourcemanager(resourcemanager)
	{
		connect(&resourcemanager, &ResourceManager::deviceready, this, [this](const vk::Device& device) {
			this->init();
			},Qt::SingleShotConnection);
	}
	void DescriptorSetManager::init() {
		// 初始化池大小配置
		generalpoolSizes = {
			{vk::DescriptorType::eUniformBuffer,        1024},
			{vk::DescriptorType::eCombinedImageSampler, 1024},
			{vk::DescriptorType::eStorageBuffer,        512},
			{vk::DescriptorType::eStorageImage,         256},
			{vk::DescriptorType::eSampler,              256},
		};
		shadowpoolSizes = {
			{vk::DescriptorType::eUniformBuffer,        256},
			{vk::DescriptorType::eCombinedImageSampler, 256},
		};
		computepoolSizes = {
			{vk::DescriptorType::eStorageBuffer,  512},
			{vk::DescriptorType::eStorageImage,   512},
			{vk::DescriptorType::eSampler,        128},
		};
		tinypoolSizes = {
			{vk::DescriptorType::eUniformBuffer,        64},
			{vk::DescriptorType::eCombinedImageSampler, 64},
		};
		framepools.resize(resourcemanager.getFramesInFlight());
		// 预创建常用池
		contpools.push_back(createDescriptorPool(DescriptorPoolSizeFlag::eGeneral,
							vk::DescriptorPoolCreateFlagBits::eUpdateAfterBind));
		for (int i = 0; i < framepools.size(); ++i)
			framepools[i].push_back(createDescriptorPool(DescriptorPoolSizeFlag::eTiny,
				vk::DescriptorPoolCreateFlagBits::eUpdateAfterBind));
	}

	void DescriptorSetManager::destroy() {
		for (auto& pool : contpools) {
			if (pool) {
				pool->destroy();
			}
		}
		contpools.clear();
		for (auto& pools : framepools) {
			for (auto& pool : pools)
				if (pool) {
					pool->destroy();
				}
		}
		framepools.clear();
	}
}