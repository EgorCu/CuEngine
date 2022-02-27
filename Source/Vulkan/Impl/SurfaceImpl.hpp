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

#include <CuEngine/Vulkan/Surface.hpp>

namespace CuEngine::Vulkan::Impl
{
class Surface
{
public:
    explicit Surface(VkSurfaceKHR surface, VkInstance instance) noexcept : m_Handle(surface), m_InstanceHandle(instance)
    {}

    Surface(const Surface & other) = delete;

    Surface(Surface && other) noexcept
        : m_Handle(std::exchange(other.m_Handle, VK_NULL_HANDLE)),
          m_InstanceHandle(std::exchange(other.m_InstanceHandle, VK_NULL_HANDLE))
    {}

    Surface & operator=(const Surface & other) = delete;

    Surface & operator=(Surface && other) noexcept
    {
        if (this != &other)
        {
            std::swap(m_Handle, other.m_Handle);
            std::swap(m_InstanceHandle, other.m_InstanceHandle);
        }

        return *this;
    }

    ~Surface() noexcept
    {
        if (m_Handle)
        {
            vkDestroySurfaceKHR(m_InstanceHandle, m_Handle, nullptr);
        }
    }

    [[nodiscard]] VkSurfaceKHR GetHandle() const noexcept
    {
        return m_Handle;
    }

private:
    VkSurfaceKHR m_Handle;
    VkInstance   m_InstanceHandle;
};
} // namespace CuEngine::Vulkan::Impl
