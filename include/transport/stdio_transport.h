#pragma once

#include "transport/transport.h"
#include <string>

class stdio_transport : public transport {
public:
  stdio_transport();
  std::string receive() override;

protected:
  void send_internal(const std::string &in_message) override;
};
