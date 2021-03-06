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

#include "InstanceImpl.hpp"

#include <CuEngine/Vulkan/PhysicalDevice.hpp>

namespace CuEngine::Vulkan::Impl
{
class PhysicalDevice
{
public:
    explicit PhysicalDevice(VkPhysicalDevice handle) noexcept : m_Handle(handle)
    {}

    PhysicalDevice(const PhysicalDevice &) noexcept = default;

    PhysicalDevice(PhysicalDevice &&) noexcept = default;

    PhysicalDevice & operator=(const PhysicalDevice &) noexcept = default;

    PhysicalDevice & operator=(PhysicalDevice &&) noexcept = default;

    ~PhysicalDevice() noexcept = default;

    [[nodiscard]] std::string GetName() const
    {
        auto properties = VkPhysicalDeviceProperties();
        vkGetPhysicalDeviceProperties(m_Handle, &properties);

        return properties.deviceName;
    }

    [[nodiscard]] VkPhysicalDevice GetHandle() const noexcept
    {
        return m_Handle;
    }

private:
    VkPhysicalDevice m_Handle;
};
} // namespace CuEngine::Vulkan::Impl
