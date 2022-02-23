// MIT License
//
// Copyright (c) 2022 Egor Kupaev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>

#include <CuEngine/CuEngine.hpp>

namespace CuEngine
{

static VkInstance g_Instance = VK_NULL_HANDLE;

int Application::Run() noexcept
{
    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwInitHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwInitHint(GLFW_RESIZABLE, GLFW_FALSE);

    auto window = glfwCreateWindow(800, 600, "Initial", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create a window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Initialize Vulkan
    auto app_info = VkApplicationInfo{ .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                       .pNext              = nullptr,
                                       .pApplicationName   = "CuEngine",
                                       .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
                                       .engineVersion      = VK_MAKE_VERSION(0, 0, 1),
                                       .apiVersion         = VK_API_VERSION_1_0 };

    auto instance_info = VkInstanceCreateInfo{ .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                               .pNext                   = nullptr,
                                               .flags                   = {},
                                               .pApplicationInfo        = &app_info,
                                               .enabledLayerCount       = 0,
                                               .ppEnabledLayerNames     = nullptr,
                                               .enabledExtensionCount   = 0,
                                               .ppEnabledExtensionNames = nullptr };

    if (vkCreateInstance(&instance_info, nullptr, &g_Instance) != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    // Cleanup
    vkDestroyInstance(g_Instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
} // namespace CuEngine
