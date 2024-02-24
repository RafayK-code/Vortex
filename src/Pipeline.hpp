#pragma once
#ifndef _PIPELINE_H
#define _PIPELINE_H

#include "Device.hpp"

#include <string>
#include <vector>

namespace vtx
{

struct PipelineConfigInfo {};

class Pipeline
{
public:
    Pipeline(Device& device, const std::string& vPath, const std::string& fPath, const PipelineConfigInfo& configInfo);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
    static std::vector<char> readFile(const std::string& filepath);
    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    Device& _device;
    VkPipeline _graphicsPipeline;
    VkShaderModule _vShaderModule;
    VkShaderModule _fShaderModule;
};

}

#endif