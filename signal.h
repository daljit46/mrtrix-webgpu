#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

namespace MR {

template <typename... Args> class Signal {
  using Function = std::function<void(Args...)>;

public:
  int32_t connect(const Function &slot) {
    m_nextSlotId++;
    m_slots.insert({m_nextSlotId, slot});
    return m_nextSlotId;
  }

  int32_t connect(Function &&slot) {
    m_nextSlotId++;
    m_slots.insert({m_nextSlotId, std::move(slot)});
    return m_nextSlotId;
  }

  void disconnect(int32_t slotId) { m_slots.erase(slotId); }

  void disconnectAll() { m_slots.clear(); }

  void emit(Args... args) {
    if (m_blocked)
      return;
    for (auto &slot : m_slots) {
      slot.second(args...);
    }
  }

  void block() { m_blocked = true; }
  void unblock() { m_blocked = false; }
  bool isBlocked() const { return m_blocked; }

private:
  std::unordered_map<int32_t, Function> m_slots;
  int32_t m_nextSlotId = 0;
  bool m_blocked = false;
};
} // namespace MR