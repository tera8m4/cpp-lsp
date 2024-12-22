#include "transport/stdio_transport.h"
#include <iostream>

#if _WIN32
#include <fcntl.h>
#include <io.h>
#endif

stdio_transport::stdio_transport() {
#if _WIN32
  _setmode(_fileno(stdout), _O_BINARY);
#endif
}

void stdio_transport::send_internal(const std::string &in_message) {
  std::cout << in_message;
  std::cout.flush();
}

std::string stdio_transport::receive() { return read_message(std::cin); }
