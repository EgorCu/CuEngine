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

#include "PhysicalDeviceImpl.hpp"

#include <CuEngine/Vulkan/QueueFamily.hpp>

namespace CuEngine::Vulkan::Impl
{
class QueueFamily
{
public:
    explicit QueueFamily(const VkQueueFamilyProperties & properties, std::uint32_t index) noexcept
        : m_Properties(properties), m_Index(index)
    {}

    [[nodiscard]] bool HasGraphicsSupport() const noexcept
    {
        return m_Properties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    }

    [[nodiscard]] bool GetIndex() const noexcept
    {
        return m_Index;
    }

    [[nodiscard]] bool operator<(const QueueFamily & rhs) const noexcept
    {
        return m_Index < rhs.m_Index;
    }

private:
    VkQueueFamilyProperties m_Properties;
    std::uint32_t           m_Index;
};
} // namespace CuEngine::Vulkan::Impl
