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

#include <iterator>

#include "Impl/QueueFamilyImpl.hpp"

namespace CuEngine::Vulkan
{

QueueFamily::QueueFamily(Impl::QueueFamily && queueFamily) noexcept : m_Pimpl(std::move(queueFamily))
{}

QueueFamily::QueueFamily(const QueueFamily & other) noexcept = default;

QueueFamily::QueueFamily(QueueFamily && other) noexcept = default;

QueueFamily & QueueFamily::operator=(const QueueFamily & other) noexcept = default;

QueueFamily & QueueFamily::operator=(QueueFamily && other) noexcept = default;

QueueFamily::~QueueFamily() noexcept = default;

bool QueueFamily::HasGraphicsSupport() const noexcept
{
    return m_Pimpl->HasGraphicsSupport();
}

Impl::QueueFamily & QueueFamily::GetImpl() noexcept
{
    return *m_Pimpl;
}

const Impl::QueueFamily & QueueFamily::GetImpl() const noexcept
{
    return *m_Pimpl;
}

std::vector<QueueFamily> QueueFamily::Enumerate(PhysicalDevice & device)
{
    auto count = std::uint32_t();
    vkGetPhysicalDeviceQueueFamilyProperties(device.GetImpl().GetHandle(), &count, nullptr);

    auto queueFamiliesPointers = std::vector<VkQueueFamilyProperties>(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device.GetImpl().GetHandle(), &count, queueFamiliesPointers.data());

    auto queueFamilies = std::vector<QueueFamily>();
    queueFamilies.reserve(count);
    std::ranges::transform(queueFamiliesPointers, std::back_inserter(queueFamilies),
                           [index = 0](auto queueFamiliesProperty) mutable
                           {
                               return QueueFamily(Impl::QueueFamily(queueFamiliesProperty, index));
                           });

    return queueFamilies;
}

} // namespace CuEngine::Vulkan
