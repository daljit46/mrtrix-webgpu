#pragma once

#include <optional>
#include <webgpu/webgpu_cpp.h>

namespace MR {
namespace GUI2 {
class Window;
}

struct WGPUContext {
  wgpu::Instance instance;
  wgpu::Adapter adapter;
  wgpu::Device device;
  wgpu::Queue queue;
};

// Creates a WGPUContext with an adapter that is compatible with the given surface.
[[nodiscard]] WGPUContext createWgpuContext(const std::optional<wgpu::Surface> &compatibleSurface = std::nullopt);
} // namespace MR