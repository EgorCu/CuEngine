# MIT License
#
# Copyright (c) 2022 Egor Kupaev
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.20)
project(CuEngine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        GLFW
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)
FetchContent_MakeAvailable(GLFW)

find_package(Vulkan REQUIRED)

# Global set-up
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Werror -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif ()

add_executable(CuEngine
        Source/main.cpp
        Source/CuEngine.cpp
        Source/Platform/System.cpp
        Source/Platform/SystemBuilder.cpp
        Source/Platform/Window.cpp
        Source/Platform/WindowBuilder.cpp
        Source/Vulkan/Instance.cpp
        Source/Vulkan/InstanceBuilder.cpp
        Source/Vulkan/PhysicalDevice.cpp
        Source/Vulkan/QueueFamily.cpp
        Source/Vulkan/Device.cpp
        Source/Vulkan/DeviceBuilder.cpp
        Source/Vulkan/Queue.cpp
        Source/Vulkan/Surface.cpp
        Source/Vulkan/SurfaceBuilder.cpp
        )
target_include_directories(CuEngine PRIVATE Include)
target_link_libraries(CuEngine PRIVATE glfw Vulkan::Vulkan)
target_compile_definitions(CuEngine PRIVATE GLFW_INCLUDE_VULKAN)
