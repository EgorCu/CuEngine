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

#include <algorithm>
#include <stdexcept>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../../Platform/Impl/WindowImpl.hpp"

#include <CuEngine/Vulkan/Instance.hpp>

namespace CuEngine::Vulkan::Impl
{
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

class Instance
{
public:
    explicit Instance(const Platform::Window & window) : m_Handle(VK_NULL_HANDLE), m_Surface(VK_NULL_HANDLE)
    {
        auto enabled_extensions_count = std::uint32_t();
        auto enabled_extensions       = glfwGetRequiredInstanceExtensions(&enabled_extensions_count);

        std::ranges::for_each(
            enabled_extensions, enabled_extensions + enabled_extensions_count,
            [supported_extensions = GetSupportedExtensions()](const auto & extension)
            {
                if (std::ranges::end(supported_extensions) == std::ranges::find(supported_extensions, extension))
                {
                    throw std::runtime_error(std::string("Extension ") + extension + " not supported");
                }
            });

        auto enabled_layers = std::vector<const char *>();
#ifndef NDEBUG
        enabled_layers.emplace_back("VK_LAYER_KHRONOS_validation");
        std::ranges::for_each(enabled_layers,
                              [supported_layers = GetSupportedLayers()](const auto & layer)
                              {
                                  if (std::ranges::end(supported_layers) == std::ranges::find(supported_layers, layer))
                                  {
                                      throw std::runtime_error(std::string("Layer ") + layer + " not supported");
                                  }
                              });
#endif

        auto app_info = VkApplicationInfo{ .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                           .pNext              = nullptr,
                                           .pApplicationName   = "CuEngine",
                                           .applicationVersion = VK_MAKE_VERSION(0, 0, 1),
                                           .engineVersion      = VK_MAKE_VERSION(0, 0, 1),
                                           .apiVersion         = VK_API_VERSION_1_0 };

        auto instance_info = VkInstanceCreateInfo{ .sType               = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                                   .pNext               = nullptr,
                                                   .flags               = {},
                                                   .pApplicationInfo    = &app_info,
                                                   .enabledLayerCount   = static_cast<uint32_t>(enabled_layers.size()),
                                                   .ppEnabledLayerNames = enabled_layers.data(),
                                                   .enabledExtensionCount   = enabled_extensions_count,
                                                   .ppEnabledExtensionNames = enabled_extensions };

        if (vkCreateInstance(&instance_info, nullptr, &m_Handle) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan instance");
        }

        auto status = glfwCreateWindowSurface(m_Handle, window.getImpl().getWindow(), nullptr, &m_Surface);
        if (status != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create a surface");
        }
    }

    Instance(const Instance &) = delete;

    Instance(Instance && other) noexcept
        : m_Handle(std::exchange(other.m_Handle, VK_NULL_HANDLE)),
          m_Surface(std::exchange(other.m_Surface, VK_NULL_HANDLE))
    {}

    Instance & operator=(const Instance &) = delete;

    Instance & operator=(Instance && other) noexcept
    {
        if (this != &other)
        {
            std::swap(m_Handle, other.m_Handle);
            std::swap(m_Surface, other.m_Surface);
        }

        return *this;
    }

    ~Instance() noexcept
    {
        vkDestroySurfaceKHR(m_Handle, m_Surface, nullptr);
        vkDestroyInstance(m_Handle, nullptr);
    }

    [[nodiscard]] VkInstance getHandle() const noexcept
    {
        return m_Handle;
    }

private:
    VkInstance   m_Handle;
    VkSurfaceKHR m_Surface;
};
} // namespace CuEngine::Vulkan::Impl
