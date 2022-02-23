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

PhysicalDevice::PhysicalDevice(const Impl::PhysicalDevice & device) noexcept : m_Pimpl(device)
{}

PhysicalDevice::PhysicalDevice(const PhysicalDevice & other) noexcept = default;

PhysicalDevice::PhysicalDevice(PhysicalDevice && other) noexcept : m_Pimpl(std::move(other.m_Pimpl))
{}

PhysicalDevice & PhysicalDevice::operator=(const PhysicalDevice & other) noexcept
{
    if (this != &other)
    {
        m_Pimpl = other.m_Pimpl;
    }

    return *this;
}

PhysicalDevice & PhysicalDevice::operator=(PhysicalDevice && other) noexcept
{
    if (this != &other)
    {
        m_Pimpl = std::move(other.m_Pimpl);
    }

    return *this;
}

PhysicalDevice::~PhysicalDevice() noexcept = default;

std::string PhysicalDevice::getName() const noexcept
{
    return m_Pimpl->getName();
}

Impl::PhysicalDevice & PhysicalDevice::getImpl() noexcept
{
    return *m_Pimpl;
}

const Impl::PhysicalDevice & PhysicalDevice::getImpl() const noexcept
{
    return *m_Pimpl;
}
std::vector<PhysicalDevice> EnumeratePhysicalDevices(const Instance & instance)
{
    auto count = std::uint32_t();
    if (vkEnumeratePhysicalDevices(instance.getImpl().getHandle(), &count, nullptr) != VK_SUCCESS)
    {
        throw std::runtime_error("No physical device found");
    }

    auto device_pointers = std::vector<VkPhysicalDevice>(count);
    if (vkEnumeratePhysicalDevices(instance.getImpl().getHandle(), &count, device_pointers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("No physical device found");
    }

    auto devices = std::vector<PhysicalDevice>();
    devices.reserve(count);
    std::ranges::transform(device_pointers, std::back_inserter(devices),
                           [](auto device_handle)
                           {
                               return PhysicalDevice(Impl::PhysicalDevice(device_handle));
                           });

    return devices;
}

//std::vector<PhysicalDevice> GetPhysicalDevices(const Instance & instance)
//{
//

//}

} // namespace CuEngine::Vulkan
