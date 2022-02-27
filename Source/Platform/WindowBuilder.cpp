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

#include "Impl/WindowBuilderImpl.hpp"

namespace CuEngine::Platform
{
WindowBuilder::WindowBuilder() : m_Pimpl()
{}

WindowBuilder::WindowBuilder(const WindowBuilder & other) = default;

WindowBuilder::WindowBuilder(WindowBuilder && other) noexcept : m_Pimpl(std::move(other.m_Pimpl))
{}

WindowBuilder & WindowBuilder::operator=(const WindowBuilder & other) = default;

WindowBuilder & WindowBuilder::operator=(WindowBuilder && other) noexcept
{
    if (this != &other)
    {
        m_Pimpl = std::move(other.m_Pimpl);
    }

    return *this;
}

WindowBuilder::~WindowBuilder() noexcept = default;

WindowBuilder & WindowBuilder::SetSystem(System & system) noexcept
{
    m_Pimpl->SetSystem(system.GetImpl());

    return *this;
}

WindowBuilder & WindowBuilder::SetWidth(std::size_t width) noexcept
{
    m_Pimpl->SetWidth(width);

    return *this;
}

WindowBuilder & WindowBuilder::SetHeight(std::size_t height) noexcept
{
    m_Pimpl->SetHeight(height);

    return *this;
}

WindowBuilder & WindowBuilder::SetTitle(const std::string & title) noexcept
{
    m_Pimpl->SetTitle(title);

    return *this;
}

Window WindowBuilder::Build() const
{
    return Window(m_Pimpl->Build());
}

Impl::WindowBuilder & WindowBuilder::GetImpl() noexcept
{
    return *m_Pimpl;
}

} // namespace CuEngine::Platform
