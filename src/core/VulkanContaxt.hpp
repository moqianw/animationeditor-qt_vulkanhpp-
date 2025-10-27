#pragma once


#include <vector>

#include "VulkanWindow.hpp"
#include "utils/utrls.hpp"

class VulkanContaxt {
public:
	VulkanContaxt();
	~VulkanContaxt();
	vk::Instance getVulkanInstance() { return instance; }
	void destroy();
protected:
private:
	friend class MainWindow;
	UT::QueueFamilyIndices queuefamilyindices;
	void initVulkanInstance();
	void initPhysicalDevice();
	UT::QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);
	void initDevice(const vk::SurfaceKHR& surface);
	vk::Instance instance = nullptr;
	vk::PhysicalDevice physicaldevice = nullptr;
	vk::Device device = nullptr;
	vk::Queue graphicsqueue = nullptr;
	vk::Queue presentqueue = nullptr;
};