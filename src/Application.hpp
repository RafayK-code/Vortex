#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#define NDEBUG

#include "Window.hpp"
#include "Pipeline.hpp"
#include "Device.hpp"

namespace vtx
{

class Application
{
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void init();
    void run();

private:
    Window _window = Window(WIDTH, HEIGHT, "Hello World");
    Device _device = Device(_window);
    Pipeline _pipe = Pipeline(
        _device, 
        "shaders/simple_shader.vert.spv", 
        "shaders/simple_shader.frag.spv", 
        Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT));
};

}

#endif