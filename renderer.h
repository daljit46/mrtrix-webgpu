#pragma once

#include <array>
#include <memory>
#include <stdint.h>

namespace MR {
class WGPUContext;
}

namespace MR::GUI2 {

class Window;
struct RendererPrivate;

class Renderer {
public:
  Renderer(WGPUContext *context, Window *window);
  ~Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&) = delete;
  Renderer &operator=(Renderer &&) = delete;

  void onFrame();

  std::array<float, 4> clearColor() const;
  void setClearColor(float r, float g, float b, float a);

private:
  void initSwapChain(int32_t width, int32_t height);

  std::unique_ptr<RendererPrivate> d;
  
  std::array<float, 4> m_clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
};

} // namespace MR::GUI2