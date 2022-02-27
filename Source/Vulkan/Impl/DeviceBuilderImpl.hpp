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

#pragma once

#include <vulkan/vulkan.h>

#include <CuEngine/Vulkan/DeviceBuilder.hpp>

#include "DeviceImpl.hpp"
#include "PhysicalDeviceImpl.hpp"
#include "QueueFamilyImpl.hpp"

#include <map>

namespace CuEngine::Vulkan::Impl
{
class DeviceBuilder
{
    struct QueueParameters
    {
        std::uint32_t      queueCount;
        std::vector<float> queuePriorities;
    };

public:
    explicit DeviceBuilder() noexcept : m_PhysicalDevice(VK_NULL_HANDLE), m_QueueMapping()
    {}

    DeviceBuilder(const DeviceBuilder & other) = default;

    DeviceBuilder(DeviceBuilder && other) noexcept = default;

    DeviceBuilder & operator=(const DeviceBuilder & other) = default;

    DeviceBuilder & operator=(DeviceBuilder && other) noexcept = default;

    ~DeviceBuilder() noexcept = default;

    DeviceBuilder & SetPhysicalDevice(PhysicalDevice & device) noexcept
    {
        m_PhysicalDevice = device.GetHandle();

        return *this;
    }

    DeviceBuilder & AddQueues(const QueueFamily & queueFamily, const std::vector<float> & queuePriorities) noexcept
    {
        m_QueueMapping[queueFamily] = QueueParameters{ .queueCount      = static_cast<uint32_t>(queuePriorities.size()),
                                                       .queuePriorities = queuePriorities };

        return *this;
    }

    [[nodiscard]] Device Build() const
    {
        auto queueInfos = std::vector<VkDeviceQueueCreateInfo>(m_QueueMapping.size());
        auto priorities = std::vector<std::vector<float>>(m_QueueMapping.size());

        std::ranges::transform(m_QueueMapping, queueInfos.begin(),
                               [](const auto & pair)
                               {
                                   const auto & [queueFamily, queueParameters] = pair;

                                   return VkDeviceQueueCreateInfo{ .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                                                   .pNext = nullptr,
                                                                   .flags = {},
                                                                   .queueFamilyIndex = queueFamily.GetIndex(),
                                                                   .queueCount       = queueParameters.queueCount,
                                                                   .pQueuePriorities =
                                                                       queueParameters.queuePriorities.data() };
                               });

        auto deviceFeatures = VkPhysicalDeviceFeatures{};

        auto requiredExtensions = std::vector<const char *>{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
        std::ranges::for_each(
            requiredExtensions,
            [supportedExtensions = GetSupportedExtensions()](const auto & extension)
            {
                if (std::ranges::end(supportedExtensions) == std::ranges::find(supportedExtensions, extension))
                {
                    throw std::runtime_error(std::string("Extension ") + extension + " not supported");
                }
            });

        auto deviceInfo = VkDeviceCreateInfo{
            .sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext                   = nullptr,
            .flags                   = {},
            .queueCreateInfoCount    = static_cast<std::uint32_t>(queueInfos.size()),
            .pQueueCreateInfos       = queueInfos.data(),
            .enabledLayerCount       = 0,
            .ppEnabledLayerNames     = nullptr,
            .enabledExtensionCount   = static_cast<std::uint32_t>(requiredExtensions.size()),
            .ppEnabledExtensionNames = requiredExtensions.data(),
            .pEnabledFeatures        = &deviceFeatures,
        };

        auto device = VkDevice(VK_NULL_HANDLE);
        if (vkCreateDevice(m_PhysicalDevice, &deviceInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a device!");
        }

        return Device(device);
    }

private:
    [[nodiscard]] std::vector<std::string> GetSupportedExtensions() const
    {
        auto count = std::uint32_t();
        if (vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &count, nullptr) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan Device extensions");
        }

        auto properties = std::vector<VkExtensionProperties>(count);
        if (vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &count, properties.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan Device extensions");
        }

        auto extensions = std::vector<std::string>(count);
        std::ranges::transform(properties, extensions.begin(),
                               [](const auto & property)
                               {
                                   return std::string(property.extensionName);
                               });

        return extensions;
    }

private:
    VkPhysicalDevice                       m_PhysicalDevice;
    std::map<QueueFamily, QueueParameters> m_QueueMapping;
};
} // namespace CuEngine::Vulkan::Impl
