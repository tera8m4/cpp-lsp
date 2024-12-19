#include "transport/transport.h"
#include <format>
#include <spdlog/spdlog.h>

void transport::send(std::string_view in_message) {
  constexpr std::string_view MESSAGE_FORMAT =
      "Content-Length: {0}\x0d\x0a\x0d\x0a{1}";
  const std::string result =
      "Content-Length: " + std::to_string(in_message.size()) + "\r\n\r\n" +
      std::string{in_message};
  send_internal(result);
}

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
    while (input.peek() != '{' && content_length > 0) {
      input.ignore(1);
    }

    std::string message(content_length, '\0');
    input.read(const_cast<char *>(message.data()), content_length);

    return message;
  }

  return std::string{};
}
