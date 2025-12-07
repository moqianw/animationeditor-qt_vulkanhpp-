#pragma once
#include <Windows.h>

#include <QWindow>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_win32.h>      // Win32 surface
#include "utils/utils.hpp"
#include "src/core/utils/CommandPool.hpp"
#include "VulkanContaxt.hpp"

#include "VulkanRenderer.hpp"

#include <QTimer>

class VulkanWindow :public QWindow {
	Q_OBJECT
signals:
	void surfaceReady(vk::SurfaceKHR surface);
public:
    VulkanWindow(VulkanContaxt& contaxt, QWindow* parent = nullptr);
	~VulkanWindow();
	vk::SurfaceKHR getSurfaceKHR() { return surface; }

	void showEvent(QShowEvent* event) override;
	bool event(QEvent* event) override;
	void destroy();
private:
	VulkanContaxt& contaxt;

	vk::SwapchainKHR swapchain = nullptr;
	vk::SurfaceKHR surface = nullptr;

	std::optional<vk::SurfaceFormatKHR> surfaceformat;
	std::optional<vk::Extent2D> swapchainextent;
	std::vector<vk::Image> swapchainImages;
	std::vector<vk::ImageView> swapchainImageViews;
	UT::CommandPool commandpool;
	VulkanRenderer renderer;

protected:
	friend class MainWindow;
	void createSurfaceKHR();
	void createSwapChain();
	void createImageView();
	void createCommandPool();
	void createRenderer();
	void renderFrame();
	QTimer updatetimer;
};