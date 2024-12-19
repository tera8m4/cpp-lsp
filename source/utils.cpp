#include "utils.h"
#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

#ifdef _WIN32
#include "windows.h"
#endif

namespace utils {
void wait_for_debugger() {
#ifdef _DEBUG
  static volatile bool spin = false;
  while (spin) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
#endif
}
} // namespace utils
