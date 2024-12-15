#pragma once
#include "request.h"
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace lsp::request::initialize {

struct client_info_t {
  std::string name;
  std::string version;
};

struct params : public base_params {
  std::optional<client_info_t> client_info;
};

void from_json(const nlohmann::json &j, client_info_t &client_info);
void from_json(const nlohmann::json &j, params &p);
} // namespace lsp::request::initialize
