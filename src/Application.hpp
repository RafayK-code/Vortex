#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"

#include <memory>
#include <vector>

namespace vtx
{

class Application
{
public:
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;

    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();

    Window _window = Window(WIDTH, HEIGHT, "Hello World");
    Device _device = Device(_window);
    SwapChain _swapChain = SwapChain(_device, _window.getExtent());
    std::unique_ptr<Pipeline> _pipeline;
    VkPipelineLayout _pipelineLayout;
    std::vector<VkCommandBuffer> _commandBuffers;
};

}

#endif