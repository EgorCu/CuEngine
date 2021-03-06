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

#include <GLFW/glfw3.h>

#include "../../Platform/Impl/WindowImpl.hpp"

#include <CuEngine/Vulkan/Instance.hpp>

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace CuEngine::Vulkan::Impl
{

class Instance
{
public:
    explicit Instance(VkInstance handle) noexcept : m_Handle(handle)
    {}

    Instance(const Instance &) = delete;

    Instance(Instance && other) noexcept : m_Handle(std::exchange(other.m_Handle, VK_NULL_HANDLE))
    {}

    Instance & operator=(const Instance &) = delete;

    Instance & operator=(Instance && other) noexcept
    {
        if (this != &other)
        {
            std::swap(m_Handle, other.m_Handle);
        }

        return *this;
    }

    ~Instance() noexcept
    {
        if (m_Handle)
        {
            vkDestroyInstance(m_Handle, nullptr);
        }
    }

    [[nodiscard]] VkInstance GetHandle() const noexcept
    {
        return m_Handle;
    }

private:
    VkInstance m_Handle;
};
} // namespace CuEngine::Vulkan::Impl
