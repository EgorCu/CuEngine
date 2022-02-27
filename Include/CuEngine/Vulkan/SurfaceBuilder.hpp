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

#include <CuEngine/Platform/Window.hpp>
#include <CuEngine/Utility/OptimizedPimpl.hpp>
#include <CuEngine/Vulkan/Instance.hpp>
#include <CuEngine/Vulkan/Surface.hpp>

namespace CuEngine::Vulkan
{
namespace Impl
{
class SurfaceBuilder;
}

class SurfaceBuilder
{
public:

public:
    explicit SurfaceBuilder() noexcept;

    SurfaceBuilder(const SurfaceBuilder & other);

    SurfaceBuilder(SurfaceBuilder && other) noexcept;

    SurfaceBuilder & operator=(const SurfaceBuilder & other);

    SurfaceBuilder & operator=(SurfaceBuilder && other) noexcept;

    ~SurfaceBuilder() noexcept;

    SurfaceBuilder & SetInstance(Instance & instance) noexcept;

    SurfaceBuilder & SetWindow(Platform::Window & window) noexcept;

    [[nodiscard]] Surface Build() const;

    [[nodiscard]] Impl::SurfaceBuilder & GetImpl() noexcept;

private:
    static constexpr auto memorySize      = sizeof(void *) * 2;
    static constexpr auto memoryAlignment = alignof(void *);

    OptimizedPimpl<Impl::SurfaceBuilder, memorySize, memoryAlignment> m_Pimpl;
};

} // namespace CuEngine::Vulkan
