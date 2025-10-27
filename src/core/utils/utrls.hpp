#pragma once

namespace UT {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		QueueFamilyIndices() = default;
		QueueFamilyIndices& operator=(const QueueFamilyIndices& other) = default;
		QueueFamilyIndices(const QueueFamilyIndices& other) = default;
		bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
	};
	struct Frame {

		vk::Semaphore imageAvailableSemaphores = nullptr;
		vk::Semaphore renderFinishedSemaphores = nullptr;
		vk::Fence inFlightFences = nullptr;
		vk::CommandBuffer commandbuffer = nullptr;
	};
}