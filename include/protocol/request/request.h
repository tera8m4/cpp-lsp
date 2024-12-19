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

inline std::string_view to_string(const request_method method) {
  switch (method) {
  case request_method::initialize:
    return "initialize";
  case request_method::initialized:
    return "initialized";
  default:
    return "undefined";
  }
}

struct base_params {
  virtual ~base_params() = default;
};

struct request {
  int id = -1;
  request_method method = request_method::none;
  std::unique_ptr<base_params> params{};
};
