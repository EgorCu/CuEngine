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

#include <vulkan/vulkan.h>

#include "DeviceImpl.hpp"
#include "QueueFamilyImpl.hpp"

#include <CuEngine/Vulkan/Queue.hpp>

namespace CuEngine::Vulkan::Impl
{
class Queue
{
public:
    explicit Queue(VkQueue queue) noexcept : m_Handle(queue)
    {}

    Queue(const Queue & other) = default;

    Queue(Queue && other) noexcept = default;

    Queue & operator=(const Queue & other) = default;

    Queue & operator=(Queue && other) noexcept = default;

    ~Queue() noexcept = default;

    [[nodiscard]] static Queue Get(Device & device, QueueFamily & queueFamily, std::uint32_t queueIndex)
    {
        auto queue = VkQueue(VK_NULL_HANDLE);
        vkGetDeviceQueue(device.GetHandle(), queueFamily.GetIndex(), queueIndex, &queue);

        return Queue(queue);
    }

private:
    VkQueue m_Handle;
};
} // namespace CuEngine::Vulkan::Impl
