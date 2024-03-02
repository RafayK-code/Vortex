#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace vtx
{

class Window 
{
public:
    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose() { return glfwWindowShouldClose(_window); }
    VkExtent2D getExtent() { return { _width, _height }; }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:
    const uint32_t _width;
    const uint32_t _height;

    std::string _title;

    GLFWwindow* _window;
};

}

#endif