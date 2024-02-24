#include "Application.hpp"

namespace vtx
{

void Application::init()
{
}

void Application::run()
{
    while(!_window.shouldClose()) 
    {
        glfwPollEvents();
    }
}

}