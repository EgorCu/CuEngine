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

#include "Impl/PhysicalDeviceImpl.hpp"

namespace CuEngine::Vulkan
{

PhysicalDevice::PhysicalDevice(Impl::PhysicalDevice && device) noexcept : m_Pimpl(std::move(device))
{}

PhysicalDevice::PhysicalDevice(const PhysicalDevice & other) noexcept = default;

PhysicalDevice::PhysicalDevice(PhysicalDevice && other) noexcept = default;

PhysicalDevice & PhysicalDevice::operator=(const PhysicalDevice & other) noexcept = default;

PhysicalDevice & PhysicalDevice::operator=(PhysicalDevice && other) noexcept = default;

PhysicalDevice::~PhysicalDevice() noexcept = default;

std::string PhysicalDevice::GetName() const
{
    return m_Pimpl->GetName();
}

Impl::PhysicalDevice & PhysicalDevice::GetImpl() noexcept
{
    return *m_Pimpl;
}

std::vector<PhysicalDevice> PhysicalDevice::Enumerate(Instance & instance)
{
    auto count = std::uint32_t();
    if (vkEnumeratePhysicalDevices(instance.GetImpl().GetHandle(), &count, nullptr) != VK_SUCCESS)
    {
        throw std::runtime_error("No physical device found");
    }

    auto devicePointers = std::vector<VkPhysicalDevice>(count);
    if (vkEnumeratePhysicalDevices(instance.GetImpl().GetHandle(), &count, devicePointers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("No physical device found");
    }

    auto devices = std::vector<PhysicalDevice>();
    devices.reserve(count);
    std::ranges::transform(devicePointers, std::back_inserter(devices),
                           [](auto deviceHandle)
                           {
                               return PhysicalDevice(Impl::PhysicalDevice(deviceHandle));
                           });

    return devices;
}

} // namespace CuEngine::Vulkan
