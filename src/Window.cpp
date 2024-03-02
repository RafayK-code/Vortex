#include "Window.hpp"

#include <iostream>
#include <stdexcept>

namespace vtx
{

Window::Window(uint32_t width, uint32_t height, const std::string& title)
    : _width(width), _height(height), _title(title)
{
    if(!glfwInit())
        throw std::runtime_error("Could not initialize glfw");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

    if (!_window)
        throw std::runtime_error("Could not create glfw window");
}

Window::~Window()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}


void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    if (glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS)
        throw std::runtime_error("Failed to create window surface");
}

}