#include "renderer.h"
#include "wgpucontext.h"
#include "window.h"
#include <webgpu/webgpu_cpp.h>

#include <iostream> 

namespace MR::GUI2 {

struct RendererPrivate {
  WGPUContext *m_context = nullptr;
  Window *m_window = nullptr;
  wgpu::Surface m_surface;
  wgpu::SwapChain m_swapChain;
};

Renderer::Renderer(WGPUContext *context, Window *window) : d(std::make_unique<RendererPrivate>()) {
  d->m_context = context;
  d->m_window = window;
  d->m_surface = d->m_window->createWGPUSurface(d->m_context->instance);
  if (!d->m_surface) {
    throw std::runtime_error("Failed to initialise surface!");
  }

  auto [windowWidth, windowHeight] = d->m_window->size();
  initSwapChain(windowWidth, windowHeight);
  
  d->m_window->framebufferResizeEvent.connect([this](int32_t width, int32_t height) {
    initSwapChain(width, height);
  });
}

Renderer::~Renderer() = default;

void Renderer::onFrame() {
  wgpu::TextureView backbuffer = d->m_swapChain.GetCurrentTextureView();
  if(!backbuffer) {
    std::cout << "Failed to get backbuffer!" << std::endl;
  }

  wgpu::CommandEncoder encoder = d->m_context->device.CreateCommandEncoder();
  wgpu::RenderPassDescriptor renderPassDesc = {};
  wgpu::RenderPassColorAttachment colorAttachment = {};
  colorAttachment.view = backbuffer;
  colorAttachment.loadOp = wgpu::LoadOp::Clear;
  colorAttachment.storeOp = wgpu::StoreOp::Store;
  colorAttachment.clearValue = {
    m_clearColor[0],
    m_clearColor[1],
    m_clearColor[2],
    m_clearColor[3]
  };
  renderPassDesc.colorAttachmentCount = 1;
  renderPassDesc.colorAttachments = &colorAttachment;

  wgpu::RenderPassEncoder renderPass = encoder.BeginRenderPass(&renderPassDesc);
  renderPass.End();

  wgpu::CommandBuffer commands = encoder.Finish();
  d->m_context->queue.Submit(1, &commands);

  d->m_swapChain.Present();
}

void Renderer::setClearColor(float r, float g, float b, float a) {
  m_clearColor = {r, g, b, a};
}

void Renderer::initSwapChain(int32_t width, int32_t height) {
  wgpu::SwapChainDescriptor swapChainDesc = {};
  swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
  swapChainDesc.format = wgpu::TextureFormat::BGRA8Unorm;
  swapChainDesc.width = width;
  swapChainDesc.height = height;
  swapChainDesc.presentMode = wgpu::PresentMode::Fifo;

  d->m_swapChain = d->m_context->device.CreateSwapChain(d->m_surface, &swapChainDesc);
}

} // namespace MR::GUI2