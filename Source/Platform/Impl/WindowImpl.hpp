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

#include <GLFW/glfw3.h>

#include <CuEngine/Platform/Window.hpp>

namespace CuEngine::Platform::Impl
{
class Window
{
public:
    Window(std::size_t width, std::size_t height, const char * name) : m_Window(nullptr)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), name, nullptr, nullptr);
        if (m_Window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create a window");
        }
    }

    Window(Window && other) noexcept : m_Window(std::exchange(other.m_Window, nullptr))
    {}

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

        glfwTerminate();
    }

    [[nodiscard]] bool shouldClose() const noexcept
    {
        return glfwWindowShouldClose(m_Window);
    }

    void pollEvents() const noexcept
    {
        glfwPollEvents();
    }

    [[nodiscard]] GLFWwindow * getWindow() const noexcept
    {
        return m_Window;
    }

private:
    GLFWwindow * m_Window;
};
} // namespace CuEngine::Platform::Impl
