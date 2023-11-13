#pragma once

#include "inputenums.h"
#include "signal.h"

#include <memory>
#include <stdint.h>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace wgpu {
class Surface;
class Instance;
} // namespace wgpu

struct GLFWwindow;

namespace MR::GUI2 {


struct KeyEvent {
  KeyAction action;
  KeyCode keyCode;
  ModifierKey modifiers;
};

class Window {
public:
  Window(std::string_view title, int32_t width, int32_t height);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(Window &&) = delete;

  [[nodiscard]] bool shouldClose() const;

  std::string title() const;
  void setTitle(const std::string &title);

  // The size the window in *screen coordinates*.
  std::tuple<int32_t, int32_t> size() const;

  // The size of the framebuffer in *pixels*.
  std::tuple<int32_t, int32_t> framebufferSize() const;

  // The ratio between the current DPI and the platform's default DPI.
  std::tuple<float, float> contentScale() const;

  // The position of the cursor in *screen coordinates* measured from the top-left corner of the window.
  std::tuple<float, float> cursorPosition() const;

  [[nodiscard]] wgpu::Surface createWGPUSurface(const wgpu::Instance &instance) const;

  static void pollEvents();

  // <width, height>
  Signal<int32_t, int32_t> resizeEvent;
  // <width, height>
  Signal<int32_t, int32_t> framebufferResizeEvent;
  Signal<KeyEvent> keyEvent;
  Signal<float, float> cursorMoveEvent;

private:
  void connectEventHandlers();

  struct GLFWwindowDeleter {
    void operator()(GLFWwindow *window) const;
  };
  using GLFWwindowPtr = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;

  GLFWwindowPtr m_window;
  std::string m_title;
};

} // namespace MR::GUI2