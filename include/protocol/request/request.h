#pragma once

#include "utils.h"
#include <memory>
#include <string_view>

template <typename T> constexpr uint32_t string_to_uint(T &&s) {
  return utils::fnv_hash(s);
}

enum class request_method : uint32_t {
  initialize = string_to_uint(std::string_view{"initialize"}),
  initialized = string_to_uint(std::string_view{"initialized"}),

  none = 0
};

struct base_params {
  virtual ~base_params() = default;
};

struct request {
  int id = -1;
  request_method method = request_method::none;
  std::unique_ptr<base_params> params{};
};
