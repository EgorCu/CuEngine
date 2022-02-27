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
#include <CuEngine/Vulkan/Queue.hpp>
#include <CuEngine/Vulkan/QueueFamily.hpp>
#include <CuEngine/Vulkan/SurfaceBuilder.hpp>

#include <algorithm>
#include <iostream>
#include <set>

namespace CuEngine
{
struct SuitableDevice
{
    Vulkan::PhysicalDevice physicalDevice;
    Vulkan::QueueFamily    graphicsQueueFamily;
    Vulkan::QueueFamily    presentationQueueFamily;
};

static Platform::System CreateSystem();

static Platform::Window CreateWindow(Platform::System & system);

static Vulkan::Instance CreateInstance();

static SuitableDevice FindSuitableDevice(Vulkan::Instance & instance, Vulkan::Surface & surface);

static Vulkan::Device CreateDevice(SuitableDevice & suitableDevice);

static Vulkan::Queue GetQueue(Vulkan::Device & device, Vulkan::QueueFamily & queueFamily);

static Vulkan::Surface CreateSurface(Vulkan::Instance & instance, Platform::Window & window);

int Application::Run() noexcept
{

    try
    {
        auto system            = CreateSystem();
        auto window            = CreateWindow(system);
        auto instance          = CreateInstance();
        auto surface           = CreateSurface(instance, window);
        auto suitableDevice    = FindSuitableDevice(instance, surface);
        auto device            = CreateDevice(suitableDevice);
        auto graphicsQueue     = GetQueue(device, suitableDevice.graphicsQueueFamily);
        auto presentationQueue = GetQueue(device, suitableDevice.presentationQueueFamily);

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

static SuitableDevice FindSuitableDevice(Vulkan::Instance & instance, Vulkan::Surface & surface)
{
    auto physicalDevices = Vulkan::PhysicalDevice::Enumerate(instance);
    auto suitableDeviceIt =
        std::ranges::find_if(physicalDevices,
                             [&surface](auto & device)
                             {
                                 return std::ranges::any_of(Vulkan::QueueFamily::Enumerate(device),
                                                            [](const auto & queueFamily)
                                                            {
                                                                return queueFamily.HasGraphicsSupport();
                                                            })
                                        && std::ranges::any_of(Vulkan::QueueFamily::Enumerate(device),
                                                               [&surface](const auto & queueFamily)
                                                               {
                                                                   return queueFamily.HasSurfaceSupport(surface);
                                                               });
                             });

    if (std::end(physicalDevices) == suitableDeviceIt)
    {
        throw std::runtime_error("Failed to find a suitable Vulkan device");
    }
    auto suitableDevice = *suitableDeviceIt;

    auto queueFamilies             = Vulkan::QueueFamily::Enumerate(suitableDevice);
    auto graphicsQueueFamilyIt     = std::ranges::find_if(queueFamilies,
                                                          [](const auto & queueFamily)
                                                          {
                                                              return queueFamily.HasGraphicsSupport();
                                                          });
    auto presentationQueueFamilyIt = std::ranges::find_if(queueFamilies,
                                                          [&surface](const auto & queueFamily)
                                                          {
                                                              return queueFamily.HasSurfaceSupport(surface);
                                                          });

    if (std::end(queueFamilies) == graphicsQueueFamilyIt || std::end(queueFamilies) == presentationQueueFamilyIt)
    {
        throw std::runtime_error("Failed to find a suitable Vulkan queue families");
    }
    auto graphicsQueueFamily     = *graphicsQueueFamilyIt;
    auto presentationQueueFamily = *presentationQueueFamilyIt;

    return { .physicalDevice          = suitableDevice,
             .graphicsQueueFamily     = graphicsQueueFamily,
             .presentationQueueFamily = presentationQueueFamily };
}

static Vulkan::Device CreateDevice(SuitableDevice & suitableDevice)
{
    auto builder = Vulkan::DeviceBuilder().SetPhysicalDevice(suitableDevice.physicalDevice);

    for (auto && queueFamily :
         std::set<Vulkan::QueueFamily>{ suitableDevice.graphicsQueueFamily, suitableDevice.presentationQueueFamily })
    {
        builder.AddQueues(queueFamily, std::vector<float>{ 1.0 });
    }

    return builder.Build();
}

static Vulkan::Queue GetQueue(Vulkan::Device & device, Vulkan::QueueFamily & queueFamily)
{
    return Vulkan::Queue::Get(device, queueFamily, 0);
}

static Vulkan::Surface CreateSurface(Vulkan::Instance & instance, Platform::Window & window)
{
    return Vulkan::SurfaceBuilder().SetInstance(instance).SetWindow(window).Build();
};

} // namespace CuEngine
