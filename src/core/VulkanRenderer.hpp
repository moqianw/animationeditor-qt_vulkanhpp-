#pragma once
#include <vulkan/vulkan.hpp>
#include "utils/utils.hpp"
#include "qobject.h"

class VulkanWindow;
class VulkanRenderer_;
using VulkanRenderer = std::unique_ptr<VulkanRenderer_>;

class VulkanRenderer_ :public QObject{
	Q_OBJECT
public:
	VulkanRenderer_(VulkanWindow& window);
	~VulkanRenderer_();
protected:
private:
	VulkanWindow& window;
	std::vector<UT::Frame> frames;
	uint32_t currentframe;
};