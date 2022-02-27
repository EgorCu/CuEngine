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

#include <CuEngine/Platform/System.hpp>
#include <CuEngine/Platform/Window.hpp>
#include <CuEngine/Utility/OptimizedPimpl.hpp>

#include <cstdint>
#include <string>

namespace CuEngine::Platform
{

namespace Impl
{
class WindowBuilder;
}

class WindowBuilder
{
public:
    WindowBuilder();

    WindowBuilder(const WindowBuilder & other);

    WindowBuilder(WindowBuilder && other) noexcept;

    WindowBuilder & operator=(const WindowBuilder & other);

    WindowBuilder & operator=(WindowBuilder && other) noexcept;

    ~WindowBuilder() noexcept;

    WindowBuilder & SetSystem(System & system) noexcept;

    WindowBuilder & SetWidth(std::size_t width) noexcept;

    WindowBuilder & SetHeight(std::size_t height) noexcept;

    WindowBuilder & SetTitle(const std::string & title) noexcept;

    [[nodiscard]] Window Build() const;

    [[nodiscard]] Impl::WindowBuilder & GetImpl() noexcept;

private:
    static constexpr auto memorySize      = sizeof(std::size_t) * 2 + sizeof(std::string);
    static constexpr auto memoryAlignment = std::max(alignof(std::size_t), alignof(std::string));

    OptimizedPimpl<Impl::WindowBuilder, memorySize, memoryAlignment> m_Pimpl;
};
} // namespace CuEngine::Platform
