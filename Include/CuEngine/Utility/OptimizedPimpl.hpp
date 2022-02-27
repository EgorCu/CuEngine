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

#include <cstdint>
#include <memory>
#include <new>
#include <type_traits>

namespace CuEngine
{
template <typename ImplT, std::size_t memSize, std::size_t alignment>
class OptimizedPimpl
{
public:
    template <typename... ArgsT>
    explicit OptimizedPimpl(ArgsT &&... args) noexcept(std::is_nothrow_constructible_v<ImplT, ArgsT...>) : m_Storage()
    {
        new (&m_Storage) ImplT(std::forward<ArgsT>(args)...);
    }

    OptimizedPimpl(const OptimizedPimpl & other) noexcept(std::is_nothrow_copy_constructible_v<ImplT>) : m_Storage()
    {
        new (&m_Storage) ImplT(*other.GetImplPointer());
    }

    OptimizedPimpl(OptimizedPimpl && other) noexcept(std::is_nothrow_move_constructible_v<ImplT>) : m_Storage()
    {
        new (&m_Storage) ImplT(std::move(*other.GetImplPointer()));
    }

    OptimizedPimpl & operator=(const OptimizedPimpl & other) noexcept(std::is_nothrow_copy_assignable_v<ImplT>)
    {
        if (this != &other)
        {
            *GetImplPointer() = *other.GetImplPointer();
        }

        return *this;
    }

    OptimizedPimpl & operator=(OptimizedPimpl && other) noexcept(std::is_nothrow_copy_assignable_v<ImplT>)
    {
        if (this != &other)
        {
            *GetImplPointer() = std::move(*other.GetImplPointer());
        }

        return *this;
    }

    // I can't use std::is_nothrow_copy_destructible_v<ImplT>, as MSVC is
    // talking about undefined ImplT type, so it can't use compiler intrinsic
    //
    // I think noexcept destructor is nice in any case
    ~OptimizedPimpl() noexcept
    {
        static_assert(memSize == sizeof(ImplT), "Provided memory size does not match with actual");
        static_assert(alignment == alignof(ImplT), "Provided memory alignment does not match with actual");

        std::destroy_at(GetImplPointer());
    }

    ImplT * operator->() noexcept
    {
        return GetImplPointer();
    }

    const ImplT * operator->() const noexcept
    {
        return GetImplPointer();
    }

    ImplT & operator*() noexcept
    {
        return *GetImplPointer();
    }

    const ImplT & operator*() const noexcept
    {
        return *GetImplPointer();
    }

private:
    ImplT * GetImplPointer() noexcept
    {
        return std::launder(reinterpret_cast<ImplT *>(&m_Storage));
    }

    const ImplT * GetImplPointer() const noexcept
    {
        return std::launder(reinterpret_cast<const ImplT *>(&m_Storage));
    }

private:
    std::aligned_storage_t<memSize, alignment> m_Storage;
};
} // namespace CuEngine
