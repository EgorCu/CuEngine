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

#include <iostream>

#include <CuEngine/CuEngine.hpp>
#include <CuEngine/Platform/Window.hpp>
#include <CuEngine/Vulkan/Instance.hpp>
#include <CuEngine/Vulkan/PhysicalDevice.hpp>

namespace CuEngine
{
int Application::Run() noexcept
{

    try
    {
        auto window   = Platform::Window(800, 600, "Test");
        auto instance = Vulkan::Instance(window);

        for (auto && physicalDevice : Vulkan::EnumeratePhysicalDevices(instance))
        {
            std::cout << physicalDevice.getName() << std::endl;
        }

        // Main loop
        while (!window.shouldClose())
        {
            window.pollEvents();
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
} // namespace CuEngine
