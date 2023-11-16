#pragma once
#include <cstdint>
#include <type_traits>

namespace MR::GUI2 {
enum class KeyAction { Press, Release, Repeat };

// clang-format off
enum class KeyCode {
  Unknown,
  Space,
  Apostrophe,
  Comma,
  Minus,
  Period,
  Slash,
  Zero,One,Two,Three,Four,Five,Six,Seven,Eight,Nine,
  Semicolon,
  Equal,
  A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
  LeftBracket,
  Backslash,
  RightBracket,
  GraveAccent,
  World1,
  World2,

  Escape,
  Enter,
  Tab,
  Backspace,
  Insert,
  Delete,
  Right,
  Left,
  Down,
  Up,
  PageUp,
  PageDown,
  Home,
  End,
  CapsLock,
  ScrollLock,
  NumLock,
  PrintScreen,
  Pause,
  F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24,F25,
  Kp0,Kp1,Kp2,Kp3,Kp4,Kp5,Kp6,Kp7,Kp8,Kp9,
  KpDecimal,
  KpDivide,
  KpMultiply,
  KpSubtract,
  KpAdd,
  KpEnter,
  KpEqual,
  LeftShift,
  LeftControl,
  LeftAlt,
  LeftSuper,
  RightShift,
  RightControl,
  RightAlt,
  RightSuper,
  Menu,
  Last
};
// clang-format on

enum class ModifierKey : int32_t {
  Shift = 0x0001,
  Control = 0x0002,
  Alt = 0x0004,
  Super = 0x0008,
  CapsLock = 0x0010,
  NumLock = 0x0020
};

inline ModifierKey operator&(ModifierKey lhs, ModifierKey rhs) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<ModifierKey>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

inline ModifierKey operator|(ModifierKey lhs, ModifierKey rhs) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<ModifierKey>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline ModifierKey operator^(ModifierKey lhs, ModifierKey rhs) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<ModifierKey>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
}

inline ModifierKey operator~(ModifierKey key) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<ModifierKey>(~static_cast<T>(key));
}

inline ModifierKey &operator&=(ModifierKey &lhs, ModifierKey rhs) {
  lhs = lhs & rhs;
  return lhs;
}

inline ModifierKey &operator|=(ModifierKey &lhs, ModifierKey rhs) {
  lhs = lhs | rhs;
  return lhs;
}

inline ModifierKey &operator^=(ModifierKey &lhs, ModifierKey rhs) {
  lhs = lhs ^ rhs;
  return lhs;
}

inline bool operator==(ModifierKey lhs, ModifierKey rhs) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<T>(lhs) == static_cast<T>(rhs);
}

inline bool operator!=(ModifierKey lhs, ModifierKey rhs) {
  using T = std::underlying_type_t<ModifierKey>;
  return static_cast<T>(lhs) != static_cast<T>(rhs);
}

} // namespace MR::GUI2
