#pragma once
#include "initialize_params.h"
#include "request.h"
#include <string_view>
#include <variant>

class request_parser {
public:
  static request parse(std::string_view request_message);
};
