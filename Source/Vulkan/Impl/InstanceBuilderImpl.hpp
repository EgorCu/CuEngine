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

#include "InstanceImpl.hpp"

#include <CuEngine/Vulkan/InstanceBuilder.hpp>

namespace CuEngine::Vulkan::Impl
{
class InstanceBuilder
{
public:
    explicit InstanceBuilder() = default;

    InstanceBuilder(const InstanceBuilder &) = default;

    InstanceBuilder(InstanceBuilder && other) noexcept = default;

    InstanceBuilder & operator=(const InstanceBuilder &) = default;

    InstanceBuilder & operator=(InstanceBuilder && other) noexcept = default;

    ~InstanceBuilder() noexcept = default;

    [[nodiscard]] Instance Build() const
    {
        auto enabledExtensionsCount = std::uint32_t();
        auto enabledExtensions      = glfwGetRequiredInstanceExtensions(&enabledExtensionsCount);

        std::ranges::for_each(
            enabledExtensions, enabledExtensions + enabledExtensionsCount,
            [supportedExtensions = GetSupportedExtensions()](const auto & extension)
            {
                if (std::ranges::end(supportedExtensions) == std::ranges::find(supportedExtensions, extension))
                {
                    throw std::runtime_error(std::string("Extension ") + extension + " not supported");
                }
            });

        auto enabledLayers = std::vector<const char *>();
#ifndef NDEBUG
        enabledLayers.emplace_back("VK_LAYER_KHRONOS_validation");
        std::ranges::for_each(enabledLayers,
                              [supportedLayers = GetSupportedLayers()](const auto & layer)
                              {
                                  if (std::ranges::end(supportedLayers) == std::ranges::find(supportedLayers, layer))
                                  {
                                      throw std::runtime_error(std::string("Layer ") + layer + " not supported");
                                  }
                              });
#endif

        auto appInfo = VkApplicationInfo{ .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                          .pNext              = nullptr,
                                          .pApplicationName   = "CuEngine",
                                          .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
                                          .engineVersion      = VK_MAKE_VERSION(0, 0, 1),
                                          .apiVersion         = VK_API_VERSION_1_0 };

        auto instanceInfo = VkInstanceCreateInfo{ .sType                 = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                                  .pNext                 = nullptr,
                                                  .flags                 = {},
                                                  .pApplicationInfo      = &appInfo,
                                                  .enabledLayerCount     = static_cast<uint32_t>(enabledLayers.size()),
                                                  .ppEnabledLayerNames   = enabledLayers.data(),
                                                  .enabledExtensionCount = enabledExtensionsCount,
                                                  .ppEnabledExtensionNames = enabledExtensions };

        auto instance = VkInstance(VK_NULL_HANDLE);
        if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan instance");
        }

        return Instance(instance);
    }

private:
    static std::vector<std::string> GetSupportedExtensions()
    {
        auto count = std::uint32_t();
        if (vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan extensions");
        }

        auto properties = std::vector<VkExtensionProperties>(count);
        if (vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan extensions");
        }

        auto extensions = std::vector<std::string>(count);
        std::ranges::transform(properties, extensions.begin(),
                               [](const auto & property)
                               {
                                   return std::string(property.extensionName);
                               });

        return extensions;
    }

    static std::vector<std::string> GetSupportedLayers()
    {
        auto count = std::uint32_t();
        if (vkEnumerateInstanceLayerProperties(&count, nullptr) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan layers");
        }

        auto properties = std::vector<VkLayerProperties>(count);
        if (vkEnumerateInstanceLayerProperties(&count, properties.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to get supported Vulkan layers");
        }

        auto layers = std::vector<std::string>(count);
        std::ranges::transform(properties, layers.begin(),
                               [](const auto & property)
                               {
                                   return std::string(property.layerName);
                               });

        return layers;
    }
};
} // namespace CuEngine::Vulkan::Impl
