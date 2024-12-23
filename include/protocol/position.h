#pragma once
#include <nlohmann/json.hpp>
namespace lsp {
struct document_position {
  int line = -1;
  int character = -1;
};

void from_json(const nlohmann::json &j, document_position &p);
} // namespace lsp
