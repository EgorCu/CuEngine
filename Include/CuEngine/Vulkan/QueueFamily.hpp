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
#include <CuEngine/Vulkan/PhysicalDevice.hpp>
#include <CuEngine/Vulkan/Surface.hpp>

#include <string_view>
#include <vector>

namespace CuEngine::Vulkan
{
namespace Impl
{
class QueueFamily;
}

class QueueFamily
{
public:
    explicit QueueFamily(Impl::QueueFamily && queueFamily) noexcept;

    QueueFamily(const QueueFamily & other) noexcept;

    QueueFamily(QueueFamily && other) noexcept;

    QueueFamily & operator=(const QueueFamily & other) noexcept;

    QueueFamily & operator=(QueueFamily && other) noexcept;

    ~QueueFamily() noexcept;

    [[nodiscard]] bool HasGraphicsSupport() const noexcept;

    [[nodiscard]] bool HasSurfaceSupport(Surface & surface) const;

    [[nodiscard]] Impl::QueueFamily & GetImpl() noexcept;

    [[nodiscard]] const Impl::QueueFamily & GetImpl() const noexcept;

    [[nodiscard]] bool operator<(const QueueFamily & queueFamily) const noexcept;

    [[nodiscard]] static std::vector<QueueFamily> Enumerate(PhysicalDevice & queueFamiliesProperty);

private:
    static constexpr auto memorySize      = sizeof(void *) + sizeof(std::uint32_t) * 2;
    static constexpr auto memoryAlignment = alignof(void *);

    OptimizedPimpl<Impl::QueueFamily, memorySize, memoryAlignment> m_Pimpl;
};

} // namespace CuEngine::Vulkan
