#pragma once
#include "request.h"
#include <nlohmann/json.hpp>
#include <string>

namespace lsp::request::workspace_symbol {
struct params : public base_params {
  std::string query;
};

void from_json(const nlohmann::json &j, params &p);
} // namespace lsp::request::workspace_symbol