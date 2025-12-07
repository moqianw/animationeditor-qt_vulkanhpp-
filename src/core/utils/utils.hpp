#pragma once
#include <fstream>
#include <glm/glm.hpp>
#include <vulkan/vulkan.hpp>
#include <optional>
namespace UT {

	/// <summary>
	/// 
	/// </summary>
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		QueueFamilyIndices() = default;
		QueueFamilyIndices& operator=(const QueueFamilyIndices& other) = default;
		QueueFamilyIndices(const QueueFamilyIndices& other) = default;
		bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
		operator bool() { return isComplete(); }
	};
	/// <summary>
	/// 
	/// </summary>
	struct Frame {

		vk::Semaphore imageAvailableSemaphores = nullptr;
		vk::Semaphore renderFinishedSemaphores = nullptr;
		vk::Fence inFlightFences = nullptr;
		vk::CommandBuffer commandbuffer = nullptr;
	};
	/// <summary>
	/// 
	/// </summary>
	class FileReader {
	public:
		FileReader() {

		}
		static std::vector<char> read(const std::string& fname) {
			std::ifstream fs(fname, std::ios::binary);
			if (!fs.is_open()) {
				throw std::runtime_error("cannot open file " + fname);
			}

			fs.seekg(0, std::ios::end);
			size_t size = fs.tellg();
			std::vector<char> buffer(size);
			fs.seekg(0, std::ios::beg);
			fs.read(buffer.data(), size);

			return buffer;
		}
		~FileReader(){}
	private:
	protected:

	};
	/// <summary>
	/// 
	/// </summary>
	class ShaderStagesCreater {
	public:
		ShaderStagesCreater(){}
		static std::optional<std::pair<vk::PipelineShaderStageCreateInfo, vk::ShaderModule>> createShaderStageCreateInfo(
			const vk::Device& device, const std::vector<char>& data,
			const vk::ShaderStageFlagBits& flag,
			const char* entername) {
			vk::PipelineShaderStageCreateInfo createinfo;
			vk::ShaderModuleCreateInfo modulecreateinfo;
			modulecreateinfo.setCodeSize(static_cast<uint32_t>(data.size()))
				.setPCode(reinterpret_cast<const uint32_t*>(data.data()));
			auto module = device.createShaderModule(modulecreateinfo);
			createinfo.setStage(flag)
				.setModule(module)
				.setPName(entername);
			return std::pair<vk::PipelineShaderStageCreateInfo, vk::ShaderModule>(createinfo, module);
		}
		~ShaderStagesCreater(){}
	private:
	protected:
	};
}

namespace UT {
	/// <summary>
	/// 
	/// </summary>
	class Vertex2 {
	public:
		glm::vec3 position;
		glm::vec4 color;
		static std::vector<vk::VertexInputAttributeDescription> getVertexInputAttributeDescription(uint32_t binding = 0) {
			std::vector<vk::VertexInputAttributeDescription> descriptions(2);
			descriptions[0]
				.setBinding(binding)
				.setLocation(0)
				.setFormat(vk::Format::eR32G32B32Sfloat)
				.setOffset(offsetof(Vertex2, position));
			descriptions[1]
				.setBinding(binding)
				.setLocation(1)
				.setFormat(vk::Format::eR32G32B32A32Sfloat)
				.setOffset(offsetof(Vertex2, color));
			return descriptions;
		}
		static vk::VertexInputBindingDescription getVertexInputBindingDescription(uint32_t binding = 0) {
			vk::VertexInputBindingDescription description;
			description.setBinding(binding)
				.setInputRate(vk::VertexInputRate::eVertex)
				.setStride(sizeof(Vertex2));
			return description;
		}
	};
	class Vertex3 {
	public:
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texcoord;
		static std::vector<vk::VertexInputAttributeDescription> getVertexInputAttributeDescription(uint32_t binding = 0) {
			std::vector<vk::VertexInputAttributeDescription> descriptions(3);
			descriptions[0]
				.setBinding(binding)
				.setLocation(0)
				.setFormat(vk::Format::eR32G32B32Sfloat)
				.setOffset(offsetof(Vertex3, position));
			descriptions[1]
				.setBinding(binding)
				.setLocation(1)
				.setFormat(vk::Format::eR32G32B32A32Sfloat)
				.setOffset(offsetof(Vertex3, color));
			descriptions[2]
				.setBinding(binding)
				.setLocation(2)
				.setFormat(vk::Format::eR32G32Sfloat)
				.setOffset(offsetof(Vertex3, texcoord));
			return descriptions;
		}
		static vk::VertexInputBindingDescription getVertexInputBindingDescription(uint32_t binding = 0) {
			vk::VertexInputBindingDescription description;
			description.setBinding(binding)
				.setInputRate(vk::VertexInputRate::eVertex)
				.setStride(sizeof(Vertex3));
			return description;
		}
	};
	class Vertex4 {
	public:
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texcoord;
		glm::vec3 normal;
		static std::vector<vk::VertexInputAttributeDescription> getVertexInputAttributeDescription(uint32_t binding = 0) {
			std::vector<vk::VertexInputAttributeDescription> descriptions(4);
			descriptions[0]
				.setBinding(binding)
				.setLocation(0)
				.setFormat(vk::Format::eR32G32B32Sfloat)
				.setOffset(offsetof(Vertex4, position));
			descriptions[1]
				.setBinding(binding)
				.setLocation(1)
				.setFormat(vk::Format::eR32G32B32A32Sfloat)
				.setOffset(offsetof(Vertex4, color));
			descriptions[2]
				.setBinding(binding)
				.setLocation(2)
				.setFormat(vk::Format::eR32G32Sfloat)
				.setOffset(offsetof(Vertex4, texcoord));
			descriptions[3]
				.setBinding(binding)
				.setLocation(3)
				.setFormat(vk::Format::eR32G32B32Sfloat)
				.setOffset(offsetof(Vertex4, normal));
			return descriptions;
		}
		static vk::VertexInputBindingDescription getVertexInputBindingDescription(uint32_t binding = 0) {
			vk::VertexInputBindingDescription description;
			description.setBinding(binding)
				.setInputRate(vk::VertexInputRate::eVertex)
				.setStride(sizeof(Vertex4));
			return description;
		}
	};


}