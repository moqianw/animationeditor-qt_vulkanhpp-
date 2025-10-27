#include "CommandPool.hpp"
#include <stdexcept>
namespace UT {
    CommandPool_::CommandPool_(const CommandPoolCreateInfo& createinfo)
        : device(createinfo.device)
    {
        if (!device) throw std::runtime_error("Create CommandPool ERROR:  not set device");
        commandPool = device.createCommandPool(createinfo.commandpoolcreateinfo);
        if (!commandPool) throw std::runtime_error("Create CommandPool ERROR: Failed to create CommandPool");
    }


    std::vector<vk::CommandBuffer> CommandPool_::allocateCommandBuffers(size_t count, vk::CommandBufferLevel level) {
        if (!device) throw std::runtime_error("Create CommandPool ERROR: CommandPool device is null");

        vk::CommandBufferAllocateInfo allocInfo;
        allocInfo.setCommandPool(commandPool)
            .setLevel(level)
            .setCommandBufferCount(static_cast<uint32_t>(count));

        std::vector<vk::CommandBuffer> cmds = device.allocateCommandBuffers(allocInfo);
        commandBuffers.insert(commandBuffers.end(), cmds.begin(), cmds.end());
        return cmds;
    }


    void CommandPool_::reset(vk::CommandPoolResetFlags flags)
    {
        if (device && commandPool) {
            device.resetCommandPool(commandPool, flags);
            commandBuffers.clear(); // 记录的 CommandBuffer 已经无效
        }
    }


    CommandPool_::~CommandPool_() {
        if (device && commandPool) {
            if (!commandBuffers.empty()) {
                device.freeCommandBuffers(commandPool, commandBuffers);
            }
            device.destroyCommandPool(commandPool);
            commandPool = nullptr;
        }
        commandBuffers.clear();
        device = nullptr;
    }

}
