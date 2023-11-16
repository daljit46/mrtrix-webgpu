add_library(imgui STATIC)
add_library(imgui::imgui ALIAS imgui)

set(IMGUI_SOURCES
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui.cpp
    imgui/misc/cpp/imgui_stdlib.h
    imgui/misc/cpp/imgui_stdlib.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_wgpu.h
    imgui/backends/imgui_impl_wgpu.cpp
)

target_sources(imgui PRIVATE ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
