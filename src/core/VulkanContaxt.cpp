
#include "VulkanContaxt.hpp"
#include <QDebug>

VulkanContaxt::VulkanContaxt()
{
	try {
		initVulkanInstance();
		initPhysicalDevice();
	}
	catch (const std::exception& e) {
		qDebug() << e.what();
	}
}
void VulkanContaxt::emitDeviceReady(vk::SurfaceKHR surface) {
	std::lock_guard<std::mutex> lock(devicemutex);
	initDevice(surface);
	emit deviceready();
}
VulkanContaxt::~VulkanContaxt()
{
	destroy();
}
void VulkanContaxt::destroy() {
	try {
		if (device) {
			device.waitIdle();
			device.destroy();
		}
		if (instance) instance.destroy();
	}
	catch (std::exception& e) {
		qDebug() << e.what();
	}
}
void VulkanContaxt::initVulkanInstance()
{

	// Vulkan application info
	vk::ApplicationInfo appInfo;
	appInfo.setApiVersion(VK_API_VERSION_1_3)
		.setApplicationVersion(1)
		.setEngineVersion(1)
		.setPApplicationName("MyVulkanApp")
		.setPEngineName("NoEngine");
	
	std::vector<const char*> extensions = {
		"VK_KHR_surface",
		"VK_KHR_win32_surface"
	};

	std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };

	// Create Vulkan instance
	vk::InstanceCreateInfo instanceCreateInfo;
	instanceCreateInfo.setPApplicationInfo(&appInfo)
		.setEnabledExtensionCount(static_cast<uint32_t>(extensions.size()))
		.setPEnabledExtensionNames(extensions)
		.setEnabledLayerCount(static_cast<uint32_t>(layers.size()))
		.setPEnabledLayerNames(layers);
	instance = vk::createInstance(instanceCreateInfo);
	if (!instance) throw std::runtime_error("Create VulkanInstance ERROR");
	
}

void VulkanContaxt::initPhysicalDevice()
{
	auto devices = instance.enumeratePhysicalDevices();
	for (auto& t : devices) {
		qDebug() << t.getProperties().deviceName;
	}
	physicaldevice = devices.front();
}

UT::QueueFamilyIndices VulkanContaxt::findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) {
	UT::QueueFamilyIndices indices;
	auto queueFamilies = device.getQueueFamilyProperties();
	for (uint32_t i = 0; i < queueFamilies.size(); i++) {
		if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
			indices.graphicsFamily = i;
		if (device.getSurfaceSupportKHR(i, surface))
			indices.presentFamily = i;
		if (indices.isComplete()) break;
	}
	return indices;
}
void VulkanContaxt::initDevice(const vk::SurfaceKHR& surface)
{
	if (device) return;
	queuefamilyindices = findQueueFamilies(physicaldevice, surface);
	//auto extensions = physicaldevice.enumerateDeviceExtensionProperties();
	//for (auto& ex : extensions) {
	//	std::cout << ex.extensionName << std::endl;
	//}

	std::vector<const char*> deviceExtensions = {
		"VK_KHR_swapchain"
	};
	if (queuefamilyindices.graphicsFamily.has_value()) {
		vk::DeviceQueueCreateInfo queuecreateinfo;
		float priority = 1.0f;
		queuecreateinfo.setQueueFamilyIndex(queuefamilyindices.graphicsFamily.value())
			.setPQueuePriorities(&priority)
			.setQueueCount(1);

		vk::DeviceCreateInfo createinfo;
		createinfo.setFlags(vk::DeviceCreateFlags())
			.setQueueCreateInfoCount(1)
			.setQueueCreateInfos({ queuecreateinfo })
			.setEnabledExtensionCount(static_cast<uint32_t>(deviceExtensions.size()))
			.setPEnabledExtensionNames(deviceExtensions);
		device = physicaldevice.createDevice(createinfo);

		graphicsqueue = device.getQueue(queuefamilyindices.graphicsFamily.value(), 0);
	}
	if (queuefamilyindices.presentFamily.has_value()) {
		if (queuefamilyindices.graphicsFamily.value() != queuefamilyindices.presentFamily.value()) {
			vk::DeviceQueueCreateInfo queuecreateinfo;
			float priority = 1.0f;
			queuecreateinfo.setQueueFamilyIndex(queuefamilyindices.presentFamily.value())
				.setPQueuePriorities(&priority)
				.setQueueCount(1);

			vk::DeviceCreateInfo createinfo;
			createinfo.setFlags(vk::DeviceCreateFlags())
				.setQueueCreateInfoCount(1)
				.setQueueCreateInfos({ queuecreateinfo })
				.setEnabledExtensionCount(static_cast<uint32_t>(deviceExtensions.size()))
				.setPEnabledExtensionNames(deviceExtensions);
			device = physicaldevice.createDevice(createinfo);

			presentqueue = device.getQueue(queuefamilyindices.presentFamily.value(), 0);
		}
		else presentqueue = graphicsqueue;
	}
}
