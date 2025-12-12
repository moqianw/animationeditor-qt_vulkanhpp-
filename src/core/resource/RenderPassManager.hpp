#pragma once 
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include <optional>
#include <string>
namespace RS {
	class ResourceManager;
    class RenderPassInfo {
    public:
        struct AttachmentDesc {
            vk::Format format;
            vk::SampleCountFlagBits samples;
            vk::AttachmentLoadOp loadOp;
            vk::AttachmentStoreOp storeOp;
            vk::ImageLayout initialLayout;
            vk::ImageLayout finalLayout;

            vk::AttachmentLoadOp stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
            vk::AttachmentStoreOp stencilStoreOp = vk::AttachmentStoreOp::eDontCare;

            bool operator==(const AttachmentDesc& rhs) const;
        };
        struct AttachmentReference {
            uint32_t attachment;
            vk::ImageLayout layout;
            bool operator==(const AttachmentReference& rhs) const;
		};
        struct SubpassDesc {
            vk::PipelineBindPoint bindpoint;

            std::vector<AttachmentReference> colorRefs;
            std::optional<AttachmentReference> depthRef;

            bool operator==(const SubpassDesc& rhs) const;
        };

        struct SubpassDependencyDesc {
            uint32_t srcSubpass;
            uint32_t dstSubpass;

            vk::PipelineStageFlags srcStageMask;
            vk::PipelineStageFlags dstStageMask;

            vk::AccessFlags srcAccessMask;
            vk::AccessFlags dstAccessMask;
            bool operator==(const SubpassDependencyDesc& rhs) const;
        };

        std::vector<AttachmentDesc> attachments;

        std::vector<SubpassDesc> subpasses;

        std::vector<SubpassDependencyDesc> dependencies;

        bool operator==(const RenderPassInfo& rhs) const;
    };

	struct RenderPassInfoHash {
		size_t operator()(const RenderPassInfo& k) const;
	};
	class RenderPassLoader {
	public:
		static RenderPassInfo loadFromFile(const std::string& filepath);
	};
	class RenderPassManager{
	private:
		ResourceManager& resourcemanager;
		std::unordered_map<RenderPassInfo, vk::RenderPass, RenderPassInfoHash> renderpasses;
	public:
		vk::RenderPass createRenderPass(const std::string& filepath);
		vk::RenderPass createRenderPass(const RenderPassInfo& info);
		vk::RenderPass getRenderPass(const RenderPassInfo& info);
		RenderPassManager(ResourceManager& resourcemanager);
		~RenderPassManager() = default;
		void destroy();
	};
}