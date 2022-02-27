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

#include "Impl/SurfaceBuilderImpl.hpp"

namespace CuEngine::Vulkan
{
SurfaceBuilder::SurfaceBuilder() noexcept = default;

SurfaceBuilder::SurfaceBuilder(const SurfaceBuilder & other) = default;

SurfaceBuilder::SurfaceBuilder(SurfaceBuilder && other) noexcept = default;

SurfaceBuilder & SurfaceBuilder::operator=(const SurfaceBuilder & other) = default;

SurfaceBuilder & SurfaceBuilder::operator=(SurfaceBuilder && other) noexcept = default;

SurfaceBuilder::~SurfaceBuilder() noexcept = default;

SurfaceBuilder & SurfaceBuilder::SetInstance(Instance & instance) noexcept
{
    m_Pimpl->SetInstance(instance.GetImpl());

    return *this;
}

SurfaceBuilder & SurfaceBuilder::SetWindow(Platform::Window & window) noexcept
{
    m_Pimpl->SetWindow(window.GetImpl());

    return *this;
}

Surface SurfaceBuilder::Build() const
{
    return Surface(m_Pimpl->Build());
}

Impl::SurfaceBuilder & SurfaceBuilder::GetImpl() noexcept
{
    return *m_Pimpl;
}
} // namespace CuEngine::Vulkan
