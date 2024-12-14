#pragma once

#include <string>
#include <string_view>

class transport {
public:
  static std::string read_message(std::istream &input);

  virtual void send(std::string_view in_message) = 0;
  virtual std::string receive() = 0;

  virtual ~transport() = default;
};
