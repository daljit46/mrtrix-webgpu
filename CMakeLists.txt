cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(MRtrixWebGPU 
    LANGUAGES C CXX
    VERSION 0.1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerCache)
include(FetchContent)

find_package(Threads REQUIRED)

set(DAWN_FETCH_DEPENDENCIES ON)

if (APPLE)
    set(USE_VULKAN OFF)
    set(USE_METAL ON)
else()
    set(USE_VULKAN ON)
    set(USE_METAL OFF)
endif()
set(DAWN_USE_GLFW ON)
set(DAWN_ENABLE_D3D11 OFF)
set(DAWN_ENABLE_D3D12 OFF)
set(DAWN_ENABLE_METAL ${USE_METAL})
set(DAWN_ENABLE_NULL OFF)
set(DAWN_ENABLE_DESKTOP_GL OFF)
set(DAWN_ENABLE_OPENGLES OFF)
set(DAWN_ENABLE_VULKAN ${USE_VULKAN})
set(TINT_BUILD_SPV_READER OFF)
set(DAWN_BUILD_SAMPLES OFF)
set(TINT_BUILD_CMD_TOOLS OFF)
set(TINT_BUILD_SAMPLES OFF)
set(TINT_BUILD_DOCS OFF)
set(TINT_BUILD_TESTS OFF)
set(TINT_BUILD_FUZZERS OFF)
set(TINT_BUILD_SPIRV_TOOLS_FUZZER OFF)
set(TINT_BUILD_AST_FUZZER OFF)
set(TINT_BUILD_REGEX_FUZZER OFF)
set(TINT_BUILD_BENCHMARKS OFF)
set(TINT_BUILD_TESTS OFF)
set(TINT_BUILD_AS_OTHER_OS OFF)
set(TINT_BUILD_REMOTE_COMPILE OFF)

add_subdirectory(dawn EXCLUDE_FROM_ALL)
add_subdirectory(imgui)

add_executable(mrview 
    main.cpp 
)

add_library(mrgui STATIC
    inputenums.h
    signal.h
    renderer.h renderer.cpp
    window.cpp window.h
    wgpucontext.h wgpucontext.cpp
)

target_link_libraries(mrgui PUBLIC
    webgpu_dawn
    webgpu_cpp
    webgpu_glfw
    imgui::imgui
    Threads::Threads
)

# TODO: why is this needed to link on Linux???
target_link_libraries(mrview PUBLIC
    webgpu_dawn
    webgpu_cpp
    webgpu_glfw
)

target_link_libraries(mrview PRIVATE
    mrgui
)

add_custom_target(Github SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/.github/workflows/build.yml
)
