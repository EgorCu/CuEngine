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
#include <CuEngine/Vulkan/Device.hpp>
#include <CuEngine/Vulkan/PhysicalDevice.hpp>
#include <CuEngine/Vulkan/QueueFamily.hpp>

#include <map>
#include <utility>
#include <vector>

namespace CuEngine::Vulkan
{
namespace Impl
{
class DeviceBuilder;
}

class DeviceBuilder
{
public:

public:
    explicit DeviceBuilder() noexcept;

    DeviceBuilder(const DeviceBuilder & other);

    DeviceBuilder(DeviceBuilder && other) noexcept;

    DeviceBuilder & operator=(const DeviceBuilder & other);

    DeviceBuilder & operator=(DeviceBuilder && other) noexcept;

    ~DeviceBuilder() noexcept;

    DeviceBuilder & SetPhysicalDevice(PhysicalDevice & physicalDevice) noexcept;

    DeviceBuilder & AddQueues(const QueueFamily & queueFamily, const std::vector<float> & queuePriorities);

    [[nodiscard]] Device Build() const;

    [[nodiscard]] Impl::DeviceBuilder & GetImpl() noexcept;

private:
    static constexpr auto memorySize      = sizeof(void *) + sizeof(std::map<int, int>);
    static constexpr auto memoryAlignment = std::max(alignof(void *), alignof(std::map<int, int>));

    OptimizedPimpl<Impl::DeviceBuilder, memorySize, memoryAlignment> m_Pimpl;
};

} // namespace CuEngine::Vulkan
