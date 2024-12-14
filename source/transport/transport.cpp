#include "transport/transport.h"
#include <spdlog/spdlog.h>

std::string transport::read_message(std::istream &input) {
  constexpr std::string_view content_length_header = "Content-Length: ";
  std::size_t content_length = 0;
  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    if (line.find(content_length_header) == 0) {
      auto result = std::from_chars(line.data() + content_length_header.size(),
                                    line.data() + line.size(), content_length);
      if (result.ec == std::errc::invalid_argument) {
        spdlog::info("Failed to parse content-length: {}", line);
        continue;
      }
    }

    // skip next two bytes of \r\n
    input.ignore(2);

    std::string message(content_length, '\0');
    input.get(const_cast<char *>(message.data()), content_length + 1, '\0');

    return message;
  }

  return std::string{};
}
