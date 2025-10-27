#pragma once
#include <vulkan/vulkan.hpp>
#include <vector>
#include <optional>
namespace UT {
    class CommandPoolCreateInfo {
    public:
        CommandPoolCreateInfo& setDevice(const vk::Device& device) {
            this->device = device;
            return *this;

        }
        CommandPoolCreateInfo& setCommandPoolCreateInfo(const vk::CommandPoolCreateInfo& info) {
            this->commandpoolcreateinfo = info;
            return *this;
        }
    private:
        friend class CommandPool_;
        vk::Device device = nullptr;
        vk::CommandPoolCreateInfo commandpoolcreateinfo;
    };
    class CommandPool_;
    using CommandPool = std::unique_ptr<CommandPool_>;
    class CommandPool_ {
    public:

        CommandPool_(const CommandPoolCreateInfo& createinfo);

        CommandPool_(const CommandPool_&) = delete;
        CommandPool_& operator=(const CommandPool_&) = delete;

        std::vector<vk::CommandBuffer> allocateCommandBuffers(size_t count = 1, vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary);

        void reset(vk::CommandPoolResetFlags flags = {});

        ~CommandPool_();


    private:
        vk::Device device = nullptr;
        vk::CommandPool commandPool;
        std::vector<vk::CommandBuffer> commandBuffers;
    };

}
