#pragma once


#include <vector>
#include <mutex>
#include "utils/utils.hpp"
#include "qobject.h"
#include "resource/Scene.hpp"
class VulkanContaxt: public QObject {
	Q_OBJECT
signals:
	void deviceready();
public slots:
	void emitDeviceReady(vk::SurfaceKHR surface);
public:
	VulkanContaxt();
	~VulkanContaxt();
	vk::Instance getVulkanInstance() { return instance; }
	vk::Device getDevice() { return device; }
	vk::PhysicalDevice getPhysicalDevice() { return physicaldevice; }
	UT::QueueFamilyIndices getQueueFamilyIndices() { return queuefamilyindices; }

	void destroy();
protected:
private:
	std::mutex devicemutex;
	friend class MainWindow;
	vk::Instance instance = nullptr;
	vk::PhysicalDevice physicaldevice = nullptr;
	vk::Device device = nullptr;
	vk::Queue graphicsqueue = nullptr;
	vk::Queue presentqueue = nullptr;
	UT::QueueFamilyIndices queuefamilyindices;
	void initVulkanInstance();
	void initPhysicalDevice();
	UT::QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);
	void initDevice(const vk::SurfaceKHR& surface);
	RS::Scene scene;

	bool isemitdeviceready = false;//是否发送过deviceready信号
};