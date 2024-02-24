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
    Window(int width, int height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    inline bool shouldClose() { return glfwWindowShouldClose(_window); }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

private:
    const int _width;
    const int _height;

    std::string _title;

    GLFWwindow* _window;
};

}

#endif