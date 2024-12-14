#include "transport/stdio_transport.h"
#include <iostream>

void stdio_transport::send(const std::string_view in_message) {
  std::cout << in_message;
  std::cout.flush();
}

std::string stdio_transport::receive() { return read_message(std::cin); }
