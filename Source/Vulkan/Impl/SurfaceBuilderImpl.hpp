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

#include "../../Platform/Impl/WindowImpl.hpp"
#include "InstanceImpl.hpp"
#include "SurfaceImpl.hpp"

#include <CuEngine/Vulkan/SurfaceBuilder.hpp>

namespace CuEngine::Vulkan::Impl
{
class SurfaceBuilder
{
public:
    explicit SurfaceBuilder() noexcept : m_Instance(VK_NULL_HANDLE), m_Window(nullptr)
    {}

    SurfaceBuilder(const SurfaceBuilder & other) = default;

    SurfaceBuilder(SurfaceBuilder && other) noexcept = default;

    SurfaceBuilder & operator=(const SurfaceBuilder & other) = default;

    SurfaceBuilder & operator=(SurfaceBuilder && other) noexcept = default;

    ~SurfaceBuilder() noexcept = default;

    SurfaceBuilder & SetInstance(Instance & instance) noexcept
    {
        m_Instance = instance.GetHandle();

        return *this;
    }

    SurfaceBuilder & SetWindow(Platform::Impl::Window & window) noexcept
    {
        m_Window = window.GetWindow();

        return *this;
    }

    [[nodiscard]] Surface Build() const
    {
        auto surface = VkSurfaceKHR(VK_NULL_HANDLE);
        if (glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Vulkan surface");
        }

        return Surface(surface, m_Instance);
    }

private:
    VkInstance   m_Instance;
    GLFWwindow * m_Window;
};
} // namespace CuEngine::Vulkan::Impl
