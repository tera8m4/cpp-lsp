#pragma once

#include <string>
#include <string_view>

class transport {
public:
  static std::string read_message(std::istream &input);

  void send(std::string_view in_message);
  virtual std::string receive() = 0;

  virtual ~transport() = default;

protected:
  virtual void send_internal(const std::string &in_message) = 0;
};
