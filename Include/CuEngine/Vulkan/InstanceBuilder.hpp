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
#include <CuEngine/Vulkan/Instance.hpp>

#include <string>
#include <vector>

namespace CuEngine::Vulkan
{
namespace Impl
{
class InstanceBuilder;
}

class InstanceBuilder
{
public:
    InstanceBuilder() noexcept;

    InstanceBuilder(const InstanceBuilder &) noexcept;

    InstanceBuilder(InstanceBuilder && other) noexcept;

    InstanceBuilder & operator=(const InstanceBuilder &) noexcept;

    InstanceBuilder & operator=(InstanceBuilder && other) noexcept;

    ~InstanceBuilder() noexcept;

    [[nodiscard]] Instance Build() const;

    [[nodiscard]] Impl::InstanceBuilder & GetImpl() noexcept;

private:
    static constexpr auto memorySize      = sizeof(char);
    static constexpr auto memoryAlignment = alignof(char);

    OptimizedPimpl<Impl::InstanceBuilder, memorySize, memoryAlignment> m_Pimpl;
};
} // namespace CuEngine::Vulkan
