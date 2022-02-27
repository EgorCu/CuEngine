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

#include <CuEngine/Utility/OptimizedPimpl.hpp>

namespace CuEngine::Vulkan
{
namespace Impl
{
class Surface;
}

class Surface
{
public:
    explicit Surface(Impl::Surface && surface) noexcept;

    Surface(const Surface &) noexcept = delete;

    Surface(Surface && other) noexcept;

    Surface & operator=(const Surface &) noexcept = delete;

    Surface & operator=(Surface && other) noexcept;

    ~Surface() noexcept;

    [[nodiscard]] Impl::Surface & getImpl() noexcept;

private:
    static constexpr auto memorySize      = sizeof(void *) * 2;
    static constexpr auto memoryAlignment = alignof(void *);

    OptimizedPimpl<Impl::Surface, memorySize, memoryAlignment> m_Pimpl;
};

} // namespace CuEngine::Vulkan
