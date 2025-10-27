#pragma once
#include <Windows.h>

#include <QWindow>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_win32.h>      // Win32 surface
#include "utils/utrls.hpp"
#include "src/core/utils/CommandPool.hpp"

class VulkanWindow :public QWindow {
	Q_OBJECT
signals:
	void surfaceReady(vk::SurfaceKHR surface);
public:
	VulkanWindow(vk::Instance instance, QWidget* parent = nullptr);
	~VulkanWindow();
	vk::SurfaceKHR getSurfaceKHR() { return surface; }
	VulkanWindow& setDevice(const vk::Device& device) { 
		this->device = device; 
		return *this;
	}
	VulkanWindow& setPhysicalDevice(const vk::PhysicalDevice& physicaldevice) { 
		this->physicaldevice = physicaldevice;
		return *this;
	}
	void showEvent(QShowEvent* event) override;
	bool event(QEvent* event) override;
	void destroy();
private:

	vk::Instance instance = nullptr;
	vk::SwapchainKHR swapchain = nullptr;
	vk::SurfaceKHR surface = nullptr;
	vk::Device device = nullptr;
	vk::PhysicalDevice physicaldevice = nullptr;
	std::optional<vk::SurfaceFormatKHR> surfaceformat;
	std::optional<vk::Extent2D> swapchainextent;
	std::vector<vk::Image> swapchainImages;
	std::vector<vk::ImageView> swapchainImageViews;
	UT::QueueFamilyIndices queuefamilyindices;
	UT::CommandPool commandpool;
protected:
	friend class MainWindow;
	void createSurfaceKHR();
	void createSwapChain(const UT::QueueFamilyIndices& queuefamilyindices);
	void createImageView();
	void createCommandPool();
};