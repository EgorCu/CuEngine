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

#include "SystemImpl.hpp"
#include "WindowImpl.hpp"

#include <CuEngine/Platform/WindowBuilder.hpp>

#include <string>

namespace CuEngine::Platform::Impl
{
class WindowBuilder
{
public:
    WindowBuilder() : m_Width(640), m_Height(480), m_Title("No Title")
    {}

    WindowBuilder(const WindowBuilder &) = default;

    WindowBuilder(WindowBuilder && other) noexcept = default;

    WindowBuilder & operator=(const WindowBuilder &) = default;

    WindowBuilder & operator=(WindowBuilder && other) noexcept = default;

    ~WindowBuilder() noexcept = default;

    WindowBuilder & SetSystem(System & system) noexcept
    {
        static_cast<void>(system);

        return *this;
    }

    WindowBuilder & SetWidth(std::size_t width) noexcept
    {
        m_Width = width;

        return *this;
    }

    WindowBuilder & SetHeight(std::size_t height) noexcept
    {
        m_Height = height;

        return *this;
    }

    WindowBuilder & SetTitle(const std::string & title)
    {
        m_Title = title;

        return *this;
    }

    [[nodiscard]] Window Build() const
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        auto window =
            glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_Title.c_str(), nullptr, nullptr);
        if (window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create a window");
        }

        return Window(window);
    }

private:
    std::size_t m_Width;
    std::size_t m_Height;
    std::string m_Title;
};
} // namespace CuEngine::Platform::Impl
