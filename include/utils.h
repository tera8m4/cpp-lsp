#pragma once
#include <cstdint>
namespace utils {
template <typename T> constexpr uint32_t fnv_hash(T &&s) {
  constexpr uint32_t FNM_PRIME = 16777619u;
  constexpr uint32_t OFFSET_BASIS = 2166136261u;

  uint32_t hash = OFFSET_BASIS;
  for (const char c : s) {
    hash ^= static_cast<uint32_t>(c);
    hash *= FNM_PRIME;
  }

  return hash;
}

void wait_for_debugger();

} // namespace utils
