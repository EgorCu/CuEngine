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

#include <CuEngine/CuEngine.hpp>
#include <CuEngine/Platform/SystemBuilder.hpp>
#include <CuEngine/Platform/WindowBuilder.hpp>
#include <CuEngine/Vulkan/DeviceBuilder.hpp>
#include <CuEngine/Vulkan/InstanceBuilder.hpp>
#include <CuEngine/Vulkan/PhysicalDevice.hpp>
#include <CuEngine/Vulkan/QueueFamily.hpp>

#include <algorithm>
#include <iostream>

namespace CuEngine
{
static Platform::System CreateSystem();

static Platform::Window CreateWindow(Platform::System & system);

static Vulkan::Instance CreateInstance();

static Vulkan::PhysicalDevice FindSuitableDevice(Vulkan::Instance & instance);

static Vulkan::Device CreateDevice(Vulkan::PhysicalDevice & physicalDevice);

int Application::Run() noexcept
{

    try
    {
        auto system         = CreateSystem();
        auto window         = CreateWindow(system);
        auto instance       = CreateInstance();
        auto physicalDevice = FindSuitableDevice(instance);
        auto device         = CreateDevice(physicalDevice);

        std::cout << "Found: " << physicalDevice.GetName() << std::endl;

        // Main loop
        while (!window.ShouldClose())
        {
            window.PollEvents();
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

static Platform::System CreateSystem()
{
    return Platform::SystemBuilder().Build();
}

static Platform::Window CreateWindow(Platform::System & system)
{
    constexpr auto width  = 800;
    constexpr auto height = 600;
    constexpr auto name   = "CuEngine";

    return Platform::WindowBuilder().SetSystem(system).SetWidth(width).SetHeight(height).SetTitle(name).Build();
}

static Vulkan::Instance CreateInstance()
{
    return Vulkan::InstanceBuilder().Build();
}

static Vulkan::PhysicalDevice FindSuitableDevice(Vulkan::Instance & instance)
{
    auto physicalDevices = Vulkan::PhysicalDevice::Enumerate(instance);

    auto suitableDeviceIt =
        std::ranges::find_if(physicalDevices,
                             [](auto & device)
                             {
                                 return std::ranges::any_of(Vulkan::QueueFamily::Enumerate(device),
                                                            [](const auto & queueFamily)
                                                            {
                                                                return queueFamily.HasGraphicsSupport();
                                                            });
                             });

    if (std::end(physicalDevices) == suitableDeviceIt)
    {
        throw std::runtime_error("Failed to find a suitable Vulkan device");
    }

    return *suitableDeviceIt;
}

static Vulkan::Device CreateDevice(Vulkan::PhysicalDevice & physicalDevice)
{
    auto queueFamilies = Vulkan::QueueFamily::Enumerate(physicalDevice);

    auto graphicsQueueIt = std::ranges::find_if(queueFamilies,
                                                [](const auto & queueFamily)
                                                {
                                                    return queueFamily.HasGraphicsSupport();
                                                });

    return Vulkan::DeviceBuilder()
        .SetPhysicalDevice(physicalDevice)
        .AddQueues(*graphicsQueueIt, std::vector<float>{ 1.0 })
        .Build();
}

} // namespace CuEngine
