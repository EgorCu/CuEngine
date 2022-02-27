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
#include <CuEngine/Vulkan/Instance.hpp>

#include <string_view>
#include <vector>

namespace CuEngine::Vulkan
{
namespace Impl
{
class PhysicalDevice;
}

class PhysicalDevice
{
public:
    explicit PhysicalDevice(Impl::PhysicalDevice && other) noexcept;

    PhysicalDevice(const PhysicalDevice & other) noexcept;

    PhysicalDevice(PhysicalDevice && other) noexcept;

    PhysicalDevice & operator=(const PhysicalDevice & other) noexcept;

    PhysicalDevice & operator=(PhysicalDevice && other) noexcept;

    ~PhysicalDevice() noexcept;

    [[nodiscard]] std::string GetName() const;

    [[nodiscard]] Impl::PhysicalDevice & GetImpl() noexcept;

    [[nodiscard]] static std::vector<PhysicalDevice> Enumerate(Instance & instance);

private:
    static constexpr auto memorySize      = sizeof(void *);
    static constexpr auto memoryAlignment = alignof(void *);

    OptimizedPimpl<Impl::PhysicalDevice, memorySize, memoryAlignment> m_Pimpl;
};

} // namespace CuEngine::Vulkan
