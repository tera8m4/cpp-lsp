#pragma once

#include "utils.h"
#include <memory>
#include <string_view>

namespace lsp::request::method {
constexpr std::string_view initialize = "initialize";
constexpr std::string_view initialized = "initialized";
constexpr std::string_view textDocumentDidOpen = "textDocument/didOpen";
} // namespace lsp::request::method

template <typename T> constexpr uint32_t string_to_uint(T &&s) {
  return utils::fnv_hash(s);
}

enum class request_method : uint32_t {
  initialize = string_to_uint(lsp::request::method::initialize),
  initialized = string_to_uint(lsp::request::method::initialized),
  textDocumentDidOpen =
      string_to_uint(lsp::request::method::textDocumentDidOpen),

  none = 0
};

inline std::string_view to_string(const request_method method) {
  switch (method) {
  case request_method::initialize:
    return lsp::request::method::initialize;
  case request_method::initialized:
    return lsp::request::method::initialized;
  case request_method::textDocumentDidOpen:
    return lsp::request::method::textDocumentDidOpen;
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
