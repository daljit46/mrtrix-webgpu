#include "wgpucontext.h"
#include "window.h"

#include <iostream>
#include <string>

namespace {
std::string backendTypeString(wgpu::BackendType backendType) {
  switch (backendType) {
  case wgpu::BackendType::Null:
    return "Null";
  case wgpu::BackendType::D3D11:
    return "D3D11";
  case wgpu::BackendType::D3D12:
    return "D3D12";
  case wgpu::BackendType::Metal:
    return "Metal";
  case wgpu::BackendType::Vulkan:
    return "Vulkan";
  case wgpu::BackendType::OpenGL:
    return "OpenGL";
  case wgpu::BackendType::OpenGLES:
    return "OpenGLES";
  default:
    return "Unknown";
  }
}
} // namespace

namespace MR {

WGPUContext createWgpuContext(const std::optional<wgpu::Surface> &compatibleSurface) {
  WGPUContext context;
  context.instance = wgpu::CreateInstance();

  wgpu::RequestAdapterOptions adapterOptions = {};
  adapterOptions.powerPreference = wgpu::PowerPreference::HighPerformance;
  if (compatibleSurface.has_value()) {
    adapterOptions.compatibleSurface = compatibleSurface.value();
  }

  auto onAdapterRequestDone =
      [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const *message, void *data) {
        using namespace std::string_literals;
        if (status != WGPURequestAdapterStatus_Success) {
          throw std::runtime_error("Could not get WebGPU adapter: "s + message);
        }
        auto *adapterPtr = static_cast<wgpu::Adapter *>(data);
        *adapterPtr = wgpu::Adapter::Acquire(adapter);
      };

  wgpu::Adapter adapter;
  context.instance.RequestAdapter(&adapterOptions, onAdapterRequestDone, &adapter);
  context.adapter = adapter;
  context.device = context.adapter.CreateDevice();
  context.queue = context.device.GetQueue();

  auto onDeviceError = [](WGPUErrorType type, char const *message, void *) {
    std::cout << "Device error: " << type << std::endl;
    if (message) {
      std::cout << "Message: " << message << std::endl;
    }
    std::cout << std::endl;
  };

  auto onDeviceLost = [](WGPUDeviceLostReason reason, char const *message, void *) {
    std::cout << "Device lost: " << reason << std::endl;
    if (message) {
      std::cout << "Message: " << message << std::endl;
    }
    std::cout << std::endl;
  };

  context.device.SetUncapturedErrorCallback(onDeviceError, nullptr);
  context.device.SetDeviceLostCallback(onDeviceLost, nullptr);
  
  wgpu::AdapterProperties adapterProperties = {};
  context.adapter.GetProperties(&adapterProperties);
  std::cout << "Adapter name: " << adapterProperties.name << std::endl;
  std::cout << "Adapter vendor: " << adapterProperties.vendorName << std::endl;
  std::cout << "Adapter device id: " << adapterProperties.deviceID << std::endl;
  std::cout << "Adapter backend type: " << backendTypeString(adapterProperties.backendType) << std::endl;
  std::cout << "Adapter driver version: " << adapterProperties.driverDescription << std::endl;

  return context;
}
} // namespace MR