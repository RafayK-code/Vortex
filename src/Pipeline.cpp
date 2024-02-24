#include "Pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace vtx
{

Pipeline::Pipeline(Device& device, const std::string& vPath, const std::string& fPath, const PipelineConfigInfo& configInfo)
    : _device(device)
{
    std::vector<char> vertCode = readFile(vPath);
    std::vector<char> fragCode = readFile(fPath);

    std::cout << "Vertex shader size: " << vertCode.size() << '\n';
    std::cout << "Fragment shader size: " << fragCode.size() << '\n';
}

Pipeline::~Pipeline()
{
}

PipelineConfigInfo Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
{
    PipelineConfigInfo configInfo{};
    return configInfo;
}

std::vector<char> Pipeline::readFile(const std::string& filepath)
{
    std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filepath);

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(_device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
        throw std::runtime_error("Failed to create shader module");
}

}