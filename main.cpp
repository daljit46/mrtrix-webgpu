
#include "renderer.h"
#include "wgpucontext.h"
#include "window.h"
#include <iostream>
#include <random>

int main() {
  using namespace MR;
  GUI2::Window window("Hello World", 800, 600);

  std::array<float, 4> clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

  window.resizeEvent.connect([](int32_t width, int32_t height) {
    std::cout << "1. Window resized to " << width << "x" << height << std::endl;
  });

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 1.0f);
  window.keyEvent.connect([&clearColor, &dis, &gen](GUI2::KeyEvent event) {
    if (event.keyCode == GUI2::KeyCode::Space && event.action == GUI2::KeyAction::Press) {
      // Change clear color randomly
      clearColor[0] = dis(gen);
      clearColor[1] = dis(gen);
      clearColor[2] = dis(gen);
      clearColor[3] = 1.0f;
    }
  });

  WGPUContext context = MR::createWgpuContext();
  GUI2::Renderer renderer(&context, &window);

  while (!window.shouldClose()) {
    GUI2::Window::pollEvents();
    renderer.onFrame();
    renderer.setClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
  }

  return 0;
}