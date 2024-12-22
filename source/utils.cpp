#include "utils.h"
#include <chrono>
#include <spdlog/spdlog.h>
#include <thread>

namespace {
std::string decode_URI(const std::string_view uri) {
  std::ostringstream decoded;
  for (std::size_t i = 0; i < uri.length(); ++i) {
    if (uri[i] == '%') {
      if (!(i + 2 < uri.length() && std::isxdigit(uri[i + 1]) &&
          std::isxdigit(uri[i + 2]))) {
        return {};
      }
      int value;
      auto result =
          std::from_chars(uri.data() + i + 1, uri.data() + i + 3, value, 16);

      if (result.ec != std::errc{}) {
        return {};
      }
      decoded << static_cast<char>(value);
      i += 2;
    } else if (uri[i] == '+') {
      decoded << ' '; // Handle '+' as space (optional, depending on context)
    } else {
      decoded << uri[i];
    }
  }
  return decoded.str();
}
} // namespace

namespace utils {
void wait_for_debugger() {
#ifdef _DEBUG
  static volatile bool spin = false;
  while (spin) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
#endif
}

std::filesystem::path uri2path(std::string_view view) {
  constexpr std::string_view prefix = "file://";
  if (!view.starts_with(prefix)) {
    return {};
  }

  view.remove_prefix(prefix.size());

  // On Windows, handle "file:///" URIs for local drives
  // file:///D:/proj/
  if (view.size() >= 4 && view[2] == ':' && view[3] == '/') {
    view.remove_prefix(1);
  }
  const std::string &decoded_path = decode_URI(view);

  return std::filesystem::path(decoded_path);
}

} // namespace utils
