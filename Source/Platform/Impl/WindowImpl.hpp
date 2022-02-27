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

#include <CuEngine/Platform/Window.hpp>

#include <stdexcept>
#include <string>

namespace CuEngine::Platform::Impl
{
class Window
{
public:
    explicit Window(GLFWwindow * window) : m_Window(window)
    {}

    Window(const Window &) noexcept = delete;

    Window(Window && other) noexcept : m_Window(std::exchange(other.m_Window, nullptr))
    {}

    Window & operator=(const Window &) noexcept = delete;

    Window & operator=(Window && other) noexcept
    {
        if (this != &other)
        {
            std::swap(m_Window, other.m_Window);
        }

        return *this;
    }

    ~Window() noexcept
    {
        if (m_Window)
        {
            glfwDestroyWindow(m_Window);
        }
    }

    [[nodiscard]] bool ShouldClose() const noexcept
    {
        return glfwWindowShouldClose(m_Window);
    }

    void PollEvents() const noexcept
    {
        glfwPollEvents();
    }

    [[nodiscard]] GLFWwindow * GetWindow() const noexcept
    {
        return m_Window;
    }

private:
    GLFWwindow * m_Window;
};
} // namespace CuEngine::Platform::Impl
