#pragma once
#include <vulkan/vulkan.hpp>
#include <unordered_map>
#include <string>
#include <sstream>
namespace EG {
	static std::unordered_map<std::string, vk::Format> stringToFormatMap = {
		{"eUndefined", vk::Format::eUndefined},
		{"eR4G4UnormPack8", vk::Format::eR4G4UnormPack8},
		{"eR4G4B4A4UnormPack16", vk::Format::eR4G4B4A4UnormPack16},
		{"eB4G4R4A4UnormPack16", vk::Format::eB4G4R4A4UnormPack16},
		{"eR5G6B5UnormPack16", vk::Format::eR5G6B5UnormPack16},
		{"eB5G6R5UnormPack16", vk::Format::eB5G6R5UnormPack16},
		{"eR5G5B5A1UnormPack16", vk::Format::eR5G5B5A1UnormPack16},
		{"eB5G5R5A1UnormPack16", vk::Format::eB5G5R5A1UnormPack16},
		{"eA1R5G5B5UnormPack16", vk::Format::eA1R5G5B5UnormPack16},
		{"eR8Unorm", vk::Format::eR8Unorm},
		{"eR8Snorm", vk::Format::eR8Snorm},
		{"eR8Uscaled", vk::Format::eR8Uscaled},
		{"eR8Sscaled", vk::Format::eR8Sscaled},
		{"eR8Uint", vk::Format::eR8Uint},
		{"eR8Sint", vk::Format::eR8Sint},
		{"eR8Srgb", vk::Format::eR8Srgb},
		{"eR8G8Unorm", vk::Format::eR8G8Unorm},
		{"eR8G8Snorm", vk::Format::eR8G8Snorm},
		{"eR8G8Uscaled", vk::Format::eR8G8Uscaled},
		{"eR8G8Sscaled", vk::Format::eR8G8Sscaled},
		{"eR8G8Uint", vk::Format::eR8G8Uint},
		{"eR8G8Sint", vk::Format::eR8G8Sint},
		{"eR8G8Srgb", vk::Format::eR8G8Srgb},
		{"eR8G8B8Unorm", vk::Format::eR8G8B8Unorm},
		{"eR8G8B8Snorm", vk::Format::eR8G8B8Snorm},
		{"eR8G8B8Uscaled", vk::Format::eR8G8B8Uscaled},
		{"eR8G8B8Sscaled", vk::Format::eR8G8B8Sscaled},
		{"eR8G8B8Uint", vk::Format::eR8G8B8Uint},
		{"eR8G8B8Sint", vk::Format::eR8G8B8Sint},
		{"eR8G8B8Srgb", vk::Format::eR8G8B8Srgb},
		{"eB8G8R8Unorm", vk::Format::eB8G8R8Unorm},
		{"eB8G8R8Snorm", vk::Format::eB8G8R8Snorm},
		{"eB8G8R8Uscaled", vk::Format::eB8G8R8Uscaled},
		{"eB8G8R8Sscaled", vk::Format::eB8G8R8Sscaled},
		{"eB8G8R8Uint", vk::Format::eB8G8R8Uint},
		{"eB8G8R8Sint", vk::Format::eB8G8R8Sint},
		{"eB8G8R8Srgb", vk::Format::eB8G8R8Srgb},
		{"eR8G8B8A8Unorm", vk::Format::eR8G8B8A8Unorm},
		{"eR8G8B8A8Snorm", vk::Format::eR8G8B8A8Snorm},
		{"eR8G8B8A8Uscaled", vk::Format::eR8G8B8A8Uscaled},
		{"eR8G8B8A8Sscaled", vk::Format::eR8G8B8A8Sscaled},
		{"eR8G8B8A8Uint", vk::Format::eR8G8B8A8Uint},
		{"eR8G8B8A8Sint", vk::Format::eR8G8B8A8Sint},
		{"eR8G8B8A8Srgb", vk::Format::eR8G8B8A8Srgb},
		{"eB8G8R8A8Unorm", vk::Format::eB8G8R8A8Unorm},
		{"eB8G8R8A8Snorm", vk::Format::eB8G8R8A8Snorm},
		{"eB8G8R8A8Uscaled", vk::Format::eB8G8R8A8Uscaled},
		{"eB8G8R8A8Sscaled", vk::Format::eB8G8R8A8Sscaled},
		{"eB8G8R8A8Uint", vk::Format::eB8G8R8A8Uint},
		{"eB8G8R8A8Sint", vk::Format::eB8G8R8A8Sint},
		{"eB8G8R8A8Srgb", vk::Format::eB8G8R8A8Srgb},
		{"eA8B8G8R8UnormPack32", vk::Format::eA8B8G8R8UnormPack32},
		{"eA8B8G8R8SnormPack32", vk::Format::eA8B8G8R8SnormPack32},
		{"eA8B8G8R8UscaledPack32", vk::Format::eA8B8G8R8UscaledPack32},
		{"eA8B8G8R8SscaledPack32", vk::Format::eA8B8G8R8SscaledPack32},
		{"eA8B8G8R8UintPack32", vk::Format::eA8B8G8R8UintPack32},
		{"eA8B8G8R8SintPack32", vk::Format::eA8B8G8R8SintPack32},
		{"eA8B8G8R8SrgbPack32", vk::Format::eA8B8G8R8SrgbPack32},
		{"eA2R10G10B10UnormPack32", vk::Format::eA2R10G10B10UnormPack32},
		{"eA2R10G10B10SnormPack32", vk::Format::eA2R10G10B10SnormPack32},
		{"eA2R10G10B10UscaledPack32", vk::Format::eA2R10G10B10UscaledPack32},
		{"eA2R10G10B10SscaledPack32", vk::Format::eA2R10G10B10SscaledPack32},
		{"eA2R10G10B10UintPack32", vk::Format::eA2R10G10B10UintPack32},
		{"eA2R10G10B10SintPack32", vk::Format::eA2R10G10B10SintPack32},
		{"eA2B10G10R10UnormPack32", vk::Format::eA2B10G10R10UnormPack32},
		{"eA2B10G10R10SnormPack32", vk::Format::eA2B10G10R10SnormPack32},
		{"eA2B10G10R10UscaledPack32", vk::Format::eA2B10G10R10UscaledPack32},
		{"eA2B10G10R10SscaledPack32", vk::Format::eA2B10G10R10SscaledPack32},
		{"eA2B10G10R10UintPack32", vk::Format::eA2B10G10R10UintPack32},
		{"eA2B10G10R10SintPack32", vk::Format::eA2B10G10R10SintPack32},
		{"eA4B4G4R4UnormPack16", vk::Format::eA4B4G4R4UnormPack16},
		{"eR16Unorm", vk::Format::eR16Unorm},
		{"eR16Snorm", vk::Format::eR16Snorm},
		{"eR16Uscaled", vk::Format::eR16Uscaled},
		{"eR16Sscaled", vk::Format::eR16Sscaled},
		{"eR16Uint", vk::Format::eR16Uint},
		{"eR16Sint", vk::Format::eR16Sint},
		{"eR16Sfloat", vk::Format::eR16Sfloat},
		{"eR16G16Unorm", vk::Format::eR16G16Unorm},
		{"eR16G16Snorm", vk::Format::eR16G16Snorm},
		{"eR16G16Uscaled", vk::Format::eR16G16Uscaled},
		{"eR16G16Sscaled", vk::Format::eR16G16Sscaled},
		{"eR16G16Uint", vk::Format::eR16G16Uint},
		{"eR16G16Sint", vk::Format::eR16G16Sint},
		{"eR16G16Sfloat", vk::Format::eR16G16Sfloat},
		{"eR16G16B16Unorm", vk::Format::eR16G16B16Unorm},
		{"eR16G16B16Snorm", vk::Format::eR16G16B16Snorm},
		{"eR16G16B16Uscaled", vk::Format::eR16G16B16Uscaled},
		{"eR16G16B16Sscaled", vk::Format::eR16G16B16Sscaled},
		{"eR16G16B16Uint", vk::Format::eR16G16B16Uint},
		{"eR16G16B16Sint", vk::Format::eR16G16B16Sint},
		{"eR16G16B16Sfloat", vk::Format::eR16G16B16Sfloat},
		{"eR16G16B16A16Unorm", vk::Format::eR16G16B16A16Unorm},
		{"eR16G16B16A16Snorm", vk::Format::eR16G16B16A16Snorm},
		{"eR16G16B16A16Uscaled", vk::Format::eR16G16B16A16Uscaled},
		{"eR16G16B16A16Sscaled", vk::Format::eR16G16B16A16Sscaled},
		{"eR16G16B16A16Uint", vk::Format::eR16G16B16A16Uint},
		{"eR16G16B16A16Sint", vk::Format::eR16G16B16A16Sint},
		{"eR16G16B16A16Sfloat", vk::Format::eR16G16B16A16Sfloat},
		{"eR32Uint", vk::Format::eR32Uint},
		{"eR32Sint", vk::Format::eR32Sint},
		{"eR32Sfloat", vk::Format::eR32Sfloat},
		{"eR32G32Uint", vk::Format::eR32G32Uint},
		{"eR32G32Sint", vk::Format::eR32G32Sint},
		{"eR32G32Sfloat", vk::Format::eR32G32Sfloat},
		{"eR32G32B32Uint", vk::Format::eR32G32B32Uint},
		{"eR32G32B32Sint", vk::Format::eR32G32B32Sint},
		{"eR32G32B32Sfloat", vk::Format::eR32G32B32Sfloat},
		{"eR32G32B32A32Uint", vk::Format::eR32G32B32A32Uint},
		{"eR32G32B32A32Sint", vk::Format::eR32G32B32A32Sint},
		{"eR32G32B32A32Sfloat", vk::Format::eR32G32B32A32Sfloat},
		{"eR64Uint", vk::Format::eR64Uint},
		{"eR64Sint", vk::Format::eR64Sint},
		{"eR64Sfloat", vk::Format::eR64Sfloat},
		{"eR64G64Uint", vk::Format::eR64G64Uint},
		{"eR64G64Sint", vk::Format::eR64G64Sint},
		{"eR64G64Sfloat", vk::Format::eR64G64Sfloat},
		{"eR64G64B64Uint", vk::Format::eR64G64B64Uint},
		{"eR64G64B64Sint", vk::Format::eR64G64B64Sint},
		{"eR64G64B64Sfloat", vk::Format::eR64G64B64Sfloat},
		{"eR64G64B64A64Uint", vk::Format::eR64G64B64A64Uint},
		{"eR64G64B64A64Sint", vk::Format::eR64G64B64A64Sint},
		{"eR64G64B64A64Sfloat", vk::Format::eR64G64B64A64Sfloat},
		{"eB10G11R11UfloatPack32", vk::Format::eB10G11R11UfloatPack32},
		{"eE5B9G9R9UfloatPack32", vk::Format::eE5B9G9R9UfloatPack32},
		{"eD16Unorm", vk::Format::eD16Unorm},
		{"eX8D24UnormPack32", vk::Format::eX8D24UnormPack32},
		{"eD32Sfloat", vk::Format::eD32Sfloat},
		{"eS8Uint", vk::Format::eS8Uint},
		{"eD16UnormS8Uint", vk::Format::eD16UnormS8Uint},
		{"eD24UnormS8Uint", vk::Format::eD24UnormS8Uint},
		{"eD32SfloatS8Uint", vk::Format::eD32SfloatS8Uint},
		{"eBc1RgbUnormBlock", vk::Format::eBc1RgbUnormBlock},
		{"eBc1RgbSrgbBlock", vk::Format::eBc1RgbSrgbBlock},
		{"eBc1RgbaUnormBlock", vk::Format::eBc1RgbaUnormBlock},
		{"eBc1RgbaSrgbBlock", vk::Format::eBc1RgbaSrgbBlock},
		{"eBc2UnormBlock", vk::Format::eBc2UnormBlock},
		{"eBc2SrgbBlock", vk::Format::eBc2SrgbBlock},
		{"eBc3UnormBlock", vk::Format::eBc3UnormBlock},
		{"eBc3SrgbBlock", vk::Format::eBc3SrgbBlock},
		{"eBc4UnormBlock", vk::Format::eBc4UnormBlock},
		{"eBc4SnormBlock", vk::Format::eBc4SnormBlock},
		{"eBc5UnormBlock", vk::Format::eBc5UnormBlock},
		{"eBc5SnormBlock", vk::Format::eBc5SnormBlock},
		{"eBc6HUfloatBlock", vk::Format::eBc6HUfloatBlock},
		{"eBc6HSfloatBlock", vk::Format::eBc6HSfloatBlock},
		{"eBc7UnormBlock", vk::Format::eBc7UnormBlock},
		{"eBc7SrgbBlock", vk::Format::eBc7SrgbBlock},
		{"eEtc2R8G8B8UnormBlock", vk::Format::eEtc2R8G8B8UnormBlock},
		{"eEtc2R8G8B8SrgbBlock", vk::Format::eEtc2R8G8B8SrgbBlock},
		{"eEtc2R8G8B8A1UnormBlock", vk::Format::eEtc2R8G8B8A1UnormBlock},
		{"eEtc2R8G8B8A1SrgbBlock", vk::Format::eEtc2R8G8B8A1SrgbBlock},
		{"eEtc2R8G8B8A8UnormBlock", vk::Format::eEtc2R8G8B8A8UnormBlock},
		{"eEtc2R8G8B8A8SrgbBlock", vk::Format::eEtc2R8G8B8A8SrgbBlock},
		{"eEacR11UnormBlock", vk::Format::eEacR11UnormBlock},
		{"eEacR11SnormBlock", vk::Format::eEacR11SnormBlock},
		{"eEacR11G11UnormBlock", vk::Format::eEacR11G11UnormBlock},
		{"eEacR11G11SnormBlock", vk::Format::eEacR11G11SnormBlock},
		{"eAstc4x4UnormBlock", vk::Format::eAstc4x4UnormBlock},
		{"eAstc4x4SrgbBlock", vk::Format::eAstc4x4SrgbBlock},
		{"eAstc5x4UnormBlock", vk::Format::eAstc5x4UnormBlock},
		{"eAstc5x4SrgbBlock", vk::Format::eAstc5x4SrgbBlock},
		{"eAstc5x5UnormBlock", vk::Format::eAstc5x5UnormBlock},
		{"eAstc5x5SrgbBlock", vk::Format::eAstc5x5SrgbBlock},
		{"eAstc6x5UnormBlock", vk::Format::eAstc6x5UnormBlock},
		{"eAstc6x5SrgbBlock", vk::Format::eAstc6x5SrgbBlock},
		{"eAstc6x6UnormBlock", vk::Format::eAstc6x6UnormBlock},
		{"eAstc6x6SrgbBlock", vk::Format::eAstc6x6SrgbBlock},
		{"eAstc8x5UnormBlock", vk::Format::eAstc8x5UnormBlock},
		{"eAstc8x5SrgbBlock", vk::Format::eAstc8x5SrgbBlock},
		{"eAstc8x6UnormBlock", vk::Format::eAstc8x6UnormBlock},
		{"eAstc8x6SrgbBlock", vk::Format::eAstc8x6SrgbBlock},
		{"eAstc8x8UnormBlock", vk::Format::eAstc8x8UnormBlock},
		{"eAstc8x8SrgbBlock", vk::Format::eAstc8x8SrgbBlock},
		{"eAstc10x5UnormBlock", vk::Format::eAstc10x5UnormBlock},
		{"eAstc10x5SrgbBlock", vk::Format::eAstc10x5SrgbBlock},
		{"eAstc10x6UnormBlock", vk::Format::eAstc10x6UnormBlock},
		{"eAstc10x6SrgbBlock", vk::Format::eAstc10x6SrgbBlock},
		{"eAstc10x8UnormBlock", vk::Format::eAstc10x8UnormBlock},
		{"eAstc10x8SrgbBlock", vk::Format::eAstc10x8SrgbBlock},
		{"eAstc10x10UnormBlock", vk::Format::eAstc10x10UnormBlock},
		{"eAstc10x10SrgbBlock", vk::Format::eAstc10x10SrgbBlock},
		{"eAstc12x10UnormBlock", vk::Format::eAstc12x10UnormBlock},
		{"eAstc12x10SrgbBlock", vk::Format::eAstc12x10SrgbBlock},
		{"eAstc12x12UnormBlock", vk::Format::eAstc12x12UnormBlock},
		{"eAstc12x12SrgbBlock", vk::Format::eAstc12x12SrgbBlock}

	};

	static vk::Format stringToVkFormat(const std::string& formatString) {
		auto it = stringToFormatMap.find(formatString);
		if (it != stringToFormatMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown format string: " + formatString);
		}
	}
	static std::unordered_map<std::string, vk::SampleCountFlagBits> stringToSampleCountMap = {
		{"e1", vk::SampleCountFlagBits::e1},
		{"e2", vk::SampleCountFlagBits::e2},
		{"e4", vk::SampleCountFlagBits::e4},
		{"e8", vk::SampleCountFlagBits::e8},
		{"e16", vk::SampleCountFlagBits::e16},
		{"e32", vk::SampleCountFlagBits::e32},
		{"e64", vk::SampleCountFlagBits::e64}
	};
	static vk::SampleCountFlagBits stringToVkSampleCount(const std::string& sampleCountString) {
		auto it = stringToSampleCountMap.find(sampleCountString);
		if (it != stringToSampleCountMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown sample count string: " + sampleCountString);
		}
	}
	static std::unordered_map<std::string, vk::AttachmentLoadOp> stringToAttachmentLoadOpMap = {
		{"eLoad", vk::AttachmentLoadOp::eLoad},
		{"eClear", vk::AttachmentLoadOp::eClear},
		{"eDontCare", vk::AttachmentLoadOp::eDontCare}
	};
	static vk::AttachmentLoadOp stringToVkAttachmentLoadOp(const std::string& loadOpString) {
		auto it = stringToAttachmentLoadOpMap.find(loadOpString);
		if (it != stringToAttachmentLoadOpMap.end()) {
			return it->second;
		}
		else {
			throw std::runtime_error("Unknown load op string: " + loadOpString);
		}
	}
	static std::unordered_map<std::string, vk::AttachmentStoreOp> stringToAttachmentStoreOpMap = {
		{"eStore", vk::AttachmentStoreOp::eStore},
		{"eDontCare", vk::AttachmentStoreOp::eDontCare},
		{"eNone", vk::AttachmentStoreOp::eNone},
		{"eNoneEXT", vk::AttachmentStoreOp::eNoneEXT},
		{"eNoneKHR", vk::AttachmentStoreOp::eNoneKHR}
	};
	static vk::AttachmentStoreOp stringToVkAttachmentStoreOp(const std::string& storeOpString) {
		auto it = stringToAttachmentStoreOpMap.find(storeOpString);
		if (it != stringToAttachmentStoreOpMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown store op string: " + storeOpString);
		}
	}
	static std::unordered_map<std::string, vk::ImageLayout> stringToImageLayoutMap = {
		{"eUndefined", vk::ImageLayout::eUndefined},
		{"eGeneral", vk::ImageLayout::eGeneral},
		{"eColorAttachmentOptimal", vk::ImageLayout::eColorAttachmentOptimal},
		{"eDepthStencilAttachmentOptimal", vk::ImageLayout::eDepthStencilAttachmentOptimal},
		{"eDepthStencilReadOnlyOptimal", vk::ImageLayout::eDepthStencilReadOnlyOptimal},
		{"eShaderReadOnlyOptimal", vk::ImageLayout::eShaderReadOnlyOptimal},
		{"eTransferSrcOptimal", vk::ImageLayout::eTransferSrcOptimal},
		{"eTransferDstOptimal", vk::ImageLayout::eTransferDstOptimal},
		{"ePreinitialized", vk::ImageLayout::ePreinitialized},
		{"eDepthReadOnlyStencilAttachmentOptimal", vk::ImageLayout::eDepthReadOnlyStencilAttachmentOptimal},
		{"eDepthReadOnlyStencilAttachmentOptimalKHR", vk::ImageLayout::eDepthReadOnlyStencilAttachmentOptimalKHR},
		{"eDepthAttachmentStencilReadOnlyOptimal", vk::ImageLayout::eDepthAttachmentStencilReadOnlyOptimal},
		{"eDepthAttachmentStencilReadOnlyOptimalKHR", vk::ImageLayout::eDepthAttachmentStencilReadOnlyOptimalKHR},
		{"eDepthAttachmentOptimal", vk::ImageLayout::eDepthAttachmentOptimal},
		{"eDepthAttachmentOptimalKHR", vk::ImageLayout::eDepthAttachmentOptimalKHR},
		{"eDepthReadOnlyOptimal", vk::ImageLayout::eDepthReadOnlyOptimal},
		{"eDepthReadOnlyOptimalKHR", vk::ImageLayout::eDepthReadOnlyOptimalKHR},
		{"eStencilAttachmentOptimal", vk::ImageLayout::eStencilAttachmentOptimal},
		{"eStencilAttachmentOptimalKHR", vk::ImageLayout::eStencilAttachmentOptimalKHR},
		{"eStencilReadOnlyOptimal", vk::ImageLayout::eStencilReadOnlyOptimal},
		{"eStencilReadOnlyOptimalKHR", vk::ImageLayout::eStencilReadOnlyOptimalKHR},
		{"eReadOnlyOptimal", vk::ImageLayout::eReadOnlyOptimal},
		{"eReadOnlyOptimalKHR", vk::ImageLayout::eReadOnlyOptimalKHR},
		{"eAttachmentOptimal", vk::ImageLayout::eAttachmentOptimal},
		{"eAttachmentOptimalKHR", vk::ImageLayout::eAttachmentOptimalKHR},
		{"eRenderingLocalRead", vk::ImageLayout::eRenderingLocalRead},
		{"eRenderingLocalReadKHR", vk::ImageLayout::eRenderingLocalReadKHR},
		{"ePresentSrcKHR", vk::ImageLayout::ePresentSrcKHR},
		{"eVideoDecodeDstKHR", vk::ImageLayout::eVideoDecodeDstKHR},
		{"eVideoDecodeSrcKHR", vk::ImageLayout::eVideoDecodeSrcKHR},
		{"eVideoDecodeDpbKHR", vk::ImageLayout::eVideoDecodeDpbKHR},
		{"eSharedPresentKHR", vk::ImageLayout::eSharedPresentKHR},
		{"eFragmentDensityMapOptimalEXT", vk::ImageLayout::eFragmentDensityMapOptimalEXT},
		{"eFragmentShadingRateAttachmentOptimalKHR", vk::ImageLayout::eFragmentShadingRateAttachmentOptimalKHR},
		{"eShadingRateOptimalNV", vk::ImageLayout::eShadingRateOptimalNV},
		{"eVideoEncodeDstKHR", vk::ImageLayout::eVideoEncodeDstKHR},
		{"eVideoEncodeSrcKHR", vk::ImageLayout::eVideoEncodeSrcKHR},
		{"eVideoEncodeDpbKHR", vk::ImageLayout::eVideoEncodeDpbKHR},
		{"eAttachmentFeedbackLoopOptimalEXT", vk::ImageLayout::eAttachmentFeedbackLoopOptimalEXT},
		{"eTensorAliasingARM", vk::ImageLayout::eTensorAliasingARM},
		{"eVideoEncodeQuantizationMapKHR", vk::ImageLayout::eVideoEncodeQuantizationMapKHR},
		{"eZeroInitializedEXT", vk::ImageLayout::eZeroInitializedEXT}

	};
	static vk::ImageLayout stringToVkImageLayout(const std::string& layoutString) {
		auto it = stringToImageLayoutMap.find(layoutString);
		if (it != stringToImageLayoutMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown image layout string: " + layoutString);
		}
	}
	static std::unordered_map<std::string, vk::PipelineBindPoint> stringToPipelineBindPointMap = {
		{"eGraphics", vk::PipelineBindPoint::eGraphics},
		{"eCompute", vk::PipelineBindPoint::eCompute},
#if defined( VK_ENABLE_BETA_EXTENSIONS )
		{"eExecutionGraphAMDX", vk::PipelineBindPoint::eExecutionGraphAMDX},
#endif
		{"eRayTracingKHR", vk::PipelineBindPoint::eRayTracingKHR},
		{"eRayTracingNV", vk::PipelineBindPoint::eRayTracingNV},
		{"eSubpassShadingHUAWEI", vk::PipelineBindPoint::eSubpassShadingHUAWEI},
		{"eDataGraphARM", vk::PipelineBindPoint::eDataGraphARM}
	};
	static vk::PipelineBindPoint stringToVkPipelineBindPoint(const std::string& bindPointString) {
		auto it = stringToPipelineBindPointMap.find(bindPointString);
		if (it != stringToPipelineBindPointMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown pipeline bind point string: " + bindPointString);
		}
	}

	static std::unordered_map<std::string,vk::PipelineStageFlagBits> stringToPipelineStageFlagBitsMap = {
		{"eTopOfPipe", vk::PipelineStageFlagBits::eTopOfPipe},
		{"eDrawIndirect", vk::PipelineStageFlagBits::eDrawIndirect},
		{"eVertexInput", vk::PipelineStageFlagBits::eVertexInput},
		{"eVertexShader", vk::PipelineStageFlagBits::eVertexShader},
		{"eTessellationControlShader", vk::PipelineStageFlagBits::eTessellationControlShader},
		{"eTessellationEvaluationShader", vk::PipelineStageFlagBits::eTessellationEvaluationShader},
		{"eGeometryShader", vk::PipelineStageFlagBits::eGeometryShader},
		{"eFragmentShader", vk::PipelineStageFlagBits::eFragmentShader},
		{"eEarlyFragmentTests", vk::PipelineStageFlagBits::eEarlyFragmentTests},
		{"eLateFragmentTests", vk::PipelineStageFlagBits::eLateFragmentTests},
		{"eColorAttachmentOutput", vk::PipelineStageFlagBits::eColorAttachmentOutput},
		{"eComputeShader", vk::PipelineStageFlagBits::eComputeShader},
		{"eTransfer", vk::PipelineStageFlagBits::eTransfer},
		{"eBottomOfPipe", vk::PipelineStageFlagBits::eBottomOfPipe},
		{"eHost", vk::PipelineStageFlagBits::eHost},
		{"eAllGraphics", vk::PipelineStageFlagBits::eAllGraphics},
		{"eAllCommands", vk::PipelineStageFlagBits::eAllCommands},
		{"eNone", vk::PipelineStageFlagBits::eNone},
		{"eNoneKHR", vk::PipelineStageFlagBits::eNoneKHR},
		{"eTransformFeedbackEXT", vk::PipelineStageFlagBits::eTransformFeedbackEXT},
		{"eConditionalRenderingEXT", vk::PipelineStageFlagBits::eConditionalRenderingEXT},
		{"eAccelerationStructureBuildKHR", vk::PipelineStageFlagBits::eAccelerationStructureBuildKHR},
		{"eAccelerationStructureBuildNV", vk::PipelineStageFlagBits::eAccelerationStructureBuildNV},
		{"eRayTracingShaderKHR", vk::PipelineStageFlagBits::eRayTracingShaderKHR},
		{"eRayTracingShaderNV", vk::PipelineStageFlagBits::eRayTracingShaderNV},
		{"eFragmentDensityProcessEXT", vk::PipelineStageFlagBits::eFragmentDensityProcessEXT},
		{"eFragmentShadingRateAttachmentKHR", vk::PipelineStageFlagBits::eFragmentShadingRateAttachmentKHR},
		{"eShadingRateImageNV", vk::PipelineStageFlagBits::eShadingRateImageNV},
		{"eTaskShaderEXT", vk::PipelineStageFlagBits::eTaskShaderEXT},
		{"eTaskShaderNV", vk::PipelineStageFlagBits::eTaskShaderNV},
		{"eMeshShaderEXT", vk::PipelineStageFlagBits::eMeshShaderEXT},
		{"eMeshShaderNV", vk::PipelineStageFlagBits::eMeshShaderNV},
		{"eCommandPreprocessEXT", vk::PipelineStageFlagBits::eCommandPreprocessEXT},
		{"eCommandPreprocessNV", vk::PipelineStageFlagBits::eCommandPreprocessNV}
	};
	static vk::PipelineStageFlagBits stringToVkPipelineStageFlagBits(const std::string& stageString) {
		auto it = stringToPipelineStageFlagBitsMap.find(stageString);
		if (it != stringToPipelineStageFlagBitsMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown pipeline stage flag bits string: " + stageString);
		}
	}
	static vk::PipelineStageFlags stringToVkPipelineStageFlags(const std::string& stagesString) {
		vk::PipelineStageFlags stagesFlags{};
		if (stagesString.empty()) return stagesFlags;

		std::istringstream ss(stagesString);
		std::string stage;

		while (std::getline(ss, stage, '|')) {
			// trim
			stage.erase(0, stage.find_first_not_of(" \t\n\r\f\v"));
			stage.erase(stage.find_last_not_of(" \t\n\r\f\v") + 1);

			if (stage.empty()) continue;

			try {
				stagesFlags |= stringToVkPipelineStageFlagBits(stage);
			}
			catch (...) {
				throw std::runtime_error("Unknown PipelineStageFlagBits: " + stage);
			}
		}

		return stagesFlags;
	}

	static std::unordered_map<std::string, vk::AccessFlagBits> stringToAccessFlagBitsMap = {
		{"eIndirectCommandRead", vk::AccessFlagBits::eIndirectCommandRead},
		{"eIndexRead", vk::AccessFlagBits::eIndexRead},
		{"eVertexAttributeRead", vk::AccessFlagBits::eVertexAttributeRead},
		{"eUniformRead", vk::AccessFlagBits::eUniformRead},
		{"eInputAttachmentRead", vk::AccessFlagBits::eInputAttachmentRead},
		{"eShaderRead", vk::AccessFlagBits::eShaderRead},
		{"eShaderWrite", vk::AccessFlagBits::eShaderWrite},
		{"eColorAttachmentRead", vk::AccessFlagBits::eColorAttachmentRead},
		{"eColorAttachmentWrite", vk::AccessFlagBits::eColorAttachmentWrite},
		{"eDepthStencilAttachmentRead", vk::AccessFlagBits::eDepthStencilAttachmentRead},
		{"eDepthStencilAttachmentWrite", vk::AccessFlagBits::eDepthStencilAttachmentWrite},
		{"eTransferRead", vk::AccessFlagBits::eTransferRead},
		{"eTransferWrite", vk::AccessFlagBits::eTransferWrite},
		{"eHostRead", vk::AccessFlagBits::eHostRead},
		{"eHostWrite", vk::AccessFlagBits::eHostWrite},
		{"eMemoryRead", vk::AccessFlagBits::eMemoryRead},
		{"eMemoryWrite", vk::AccessFlagBits::eMemoryWrite},
		{"eNone", vk::AccessFlagBits::eNone},
		{"eNoneKHR", vk::AccessFlagBits::eNoneKHR},
		{"eTransformFeedbackWriteEXT", vk::AccessFlagBits::eTransformFeedbackWriteEXT},
		{"eTransformFeedbackCounterReadEXT", vk::AccessFlagBits::eTransformFeedbackCounterReadEXT},
		{"eTransformFeedbackCounterWriteEXT", vk::AccessFlagBits::eTransformFeedbackCounterWriteEXT},
		{"eConditionalRenderingReadEXT", vk::AccessFlagBits::eConditionalRenderingReadEXT},
		{"eColorAttachmentReadNoncoherentEXT", vk::AccessFlagBits::eColorAttachmentReadNoncoherentEXT},
		{"eAccelerationStructureReadKHR", vk::AccessFlagBits::eAccelerationStructureReadKHR},
		{"eAccelerationStructureReadNV", vk::AccessFlagBits::eAccelerationStructureReadNV},
		{"eAccelerationStructureWriteKHR", vk::AccessFlagBits::eAccelerationStructureWriteKHR},
		{"eAccelerationStructureWriteNV", vk::AccessFlagBits::eAccelerationStructureWriteNV},
		{"eFragmentDensityMapReadEXT", vk::AccessFlagBits::eFragmentDensityMapReadEXT},
		{"eFragmentShadingRateAttachmentReadKHR", vk::AccessFlagBits::eFragmentShadingRateAttachmentReadKHR},
		{"eShadingRateImageReadNV", vk::AccessFlagBits::eShadingRateImageReadNV},
		{"eCommandPreprocessReadEXT", vk::AccessFlagBits::eCommandPreprocessReadEXT},
		{"eCommandPreprocessReadNV", vk::AccessFlagBits::eCommandPreprocessReadNV},
		{"eCommandPreprocessWriteEXT", vk::AccessFlagBits::eCommandPreprocessWriteEXT},
		{"eCommandPreprocessWriteNV", vk::AccessFlagBits::eCommandPreprocessWriteNV}

	};
	static vk::AccessFlagBits stringToVkAccessFlagBits(const std::string& accessString) {
		auto it = stringToAccessFlagBitsMap.find(accessString);
		if (it != stringToAccessFlagBitsMap.end()) {
			return it->second;
		} else {
			throw std::runtime_error("Unknown access flag bits string: " + accessString);
		}
	}
	static vk::AccessFlags stringToVkAccessFlags(const std::string& accessesString) {
		vk::AccessFlags accessFlags{};
		if (accessesString.empty()) return accessFlags;
		std::istringstream ss(accessesString);
		std::string access;
		while (std::getline(ss, access, '|')) {
			// trim
			access.erase(0, access.find_first_not_of(" \t\n\r\f\v"));
			access.erase(access.find_last_not_of(" \t\n\r\f\v") + 1);
			if (access.empty()) continue;
			try {
				accessFlags |= stringToVkAccessFlagBits(access);
			}
			catch (...) {
				throw std::runtime_error("Unknown AccessFlagBits: " + access);
			}
		}
		return accessFlags;
	}
}