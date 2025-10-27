
#include "VulkanWindow.hpp"

#include <QDebug>
VulkanWindow::VulkanWindow(vk::Instance instance, QWidget* parent):instance(instance)
{

	setSurfaceType(QSurface::VulkanSurface);
}

VulkanWindow::~VulkanWindow()
{
	destroy();
}

void VulkanWindow::showEvent(QShowEvent* event)
{
	QWindow::showEvent(event);
	if (!surface) {
		createSurfaceKHR();
		emit surfaceReady(surface);
	}
}

bool VulkanWindow::event(QEvent* event)
{
	switch (event->type()) {
	case QEvent::Close:
		break;
	}
	return QWindow::event(event);
}
void VulkanWindow::destroy() {
	if (device) {
		if (commandpool) commandpool.reset();
		for (auto& view : this->swapchainImageViews) {
			device.destroyImageView(view);
		}
		swapchainImageViews.clear();
		if (swapchain)
			device.destroySwapchainKHR(swapchain);
		device = nullptr;
	}
	physicaldevice = nullptr;
	instance = nullptr;
	
}

void VulkanWindow::createSurfaceKHR()
{
#ifdef _WIN32
	
	VkWin32SurfaceCreateInfoKHR surfInfo{};
	surfInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfInfo.hwnd = (HWND)winId();
	surfInfo.hinstance = GetModuleHandle(nullptr);
	VkSurfaceKHR cSurface;
	vkCreateWin32SurfaceKHR(static_cast<VkInstance>(instance), &surfInfo, nullptr, &cSurface);
	surface = vk::SurfaceKHR(cSurface);
#endif
}


void VulkanWindow::createSwapChain(const UT::QueueFamilyIndices& queuefamilyindices)
{
	this->queuefamilyindices = queuefamilyindices;
	if (!physicaldevice) throw std::runtime_error("Create SwapChain ERROR: NOT SET physicaldevice");
	auto surfacecaps = physicaldevice.getSurfaceCapabilitiesKHR(surface);
	auto surfaceformats = physicaldevice.getSurfaceFormatsKHR(surface);

	auto surfacepresentmodes = physicaldevice.getSurfacePresentModesKHR(surface);
	//选择合适的format

	for (auto& format : surfaceformats) {
		if (format.format == vk::Format::eR8G8B8A8Srgb
			&& format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
		{
			surfaceformat = format;
			break;
		}
	}
	if (!surfaceformat) throw std::runtime_error("Cannot find fit format");
	//选择合适的presentmode
	std::optional<vk::PresentModeKHR> choicepresentmode;
	for (auto& presentmode : surfacepresentmodes) {
		if (presentmode == vk::PresentModeKHR::eMailbox) {
			choicepresentmode = presentmode;
			break;
		}
	}
	if (!choicepresentmode) throw std::runtime_error("Cannot find fit presentmode");


	vk::SwapchainCreateInfoKHR createinfo;
	swapchainextent = surfacecaps.currentExtent;
	createinfo.setSurface(surface)
		.setClipped(true)
		.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
		.setImageArrayLayers(1)
		.setImageFormat(surfaceformat->format)
		.setMinImageCount(
			std::clamp<uint32_t>(
				2, static_cast<uint32_t>(surfacecaps.minImageCount)
				, static_cast<uint32_t>(surfacecaps.maxImageCount))
		)
		.setImageColorSpace(surfaceformat->colorSpace)
		.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
		.setPresentMode(choicepresentmode.value())
		.setImageExtent(swapchainextent.value());
	if (queuefamilyindices.graphicsFamily.value() == queuefamilyindices.presentFamily.value()) {
		createinfo
			.setQueueFamilyIndexCount(1)
			.setQueueFamilyIndices({ queuefamilyindices.graphicsFamily.value() })
			.setImageSharingMode(vk::SharingMode::eExclusive);
	}
	else {
		uint32_t indexs[] = { queuefamilyindices.graphicsFamily.value() ,queuefamilyindices.presentFamily.value() };
		createinfo
			.setQueueFamilyIndexCount(2)
			.setQueueFamilyIndices(indexs)
			.setImageSharingMode(vk::SharingMode::eConcurrent);
	}
	if (!device) throw std::runtime_error("Create swapchain ERROR: Not set device");


	swapchain = device.createSwapchainKHR(createinfo);
}
void VulkanWindow::createImageView()
{
	swapchainImages = device.getSwapchainImagesKHR(swapchain);
	if (swapchainImages.empty()) throw std::runtime_error("Cannot get swapchain images");

	swapchainImageViews.resize(swapchainImages.size());
	vk::ImageViewCreateInfo createinfo;
	vk::ImageSubresourceRange subrange;
	subrange.setAspectMask(vk::ImageAspectFlagBits::eColor)
		.setBaseArrayLayer(0)
		.setBaseMipLevel(0)
		.setLayerCount(1)
		.setLevelCount(1);
	vk::ComponentMapping componentmapping;
	componentmapping.setA(vk::ComponentSwizzle::eA)
		.setB(vk::ComponentSwizzle::eB)
		.setG(vk::ComponentSwizzle::eG)
		.setR(vk::ComponentSwizzle::eR);
	createinfo.setFormat(surfaceformat->format)
		.setSubresourceRange(subrange)
		.setComponents(componentmapping)
		.setViewType(vk::ImageViewType::e2D)
		;


	for (uint32_t i = 0; i < swapchainImageViews.size(); i++) {
		createinfo.setImage(swapchainImages[i]);
		swapchainImageViews[i] = device.createImageView(createinfo);
	}
}
void VulkanWindow::createCommandPool() {
	UT::CommandPoolCreateInfo createinfo;
	vk::CommandPoolCreateInfo info;
	info.setQueueFamilyIndex(queuefamilyindices.graphicsFamily.value())
		.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
	createinfo.setCommandPoolCreateInfo(info)
		.setDevice(device);
	commandpool = std::make_unique<UT::CommandPool_>(createinfo);
}