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

#include <stdexcept>

#include "Impl/WindowImpl.hpp"

#include <CuEngine/Platform/Window.hpp>

namespace CuEngine::Platform
{
Window::Window(std::size_t width, std::size_t height, const char * name) : m_Pimpl(width, height, name)
{}

Window::Window(Window && other) noexcept : m_Pimpl(std::move(other.m_Pimpl))
{}

Window & Window::operator=(Window && other) noexcept
{
    if (this != &other)
    {
        m_Pimpl = std::move(other.m_Pimpl);
    }

    return *this;
}

bool Window::shouldClose() const noexcept
{
    return m_Pimpl->shouldClose();
}

void Window::pollEvents()
{
    m_Pimpl->pollEvents();
}

Window::~Window() noexcept = default;

Impl::Window & Window::getImpl() noexcept
{
    return *m_Pimpl;
}

const Impl::Window & Window::getImpl() const noexcept
{
    return *m_Pimpl;
}

} // namespace CuEngine::Platform
