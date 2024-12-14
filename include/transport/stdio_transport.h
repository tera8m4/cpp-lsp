#pragma once

#include "transport/transport.h"
#include <string_view>

class stdio_transport : public transport {
public:
  void send(std::string_view in_message) override;
  std::string receive() override;
};
