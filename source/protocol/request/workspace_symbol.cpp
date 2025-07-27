#include "protocol/request/workspace_symbol.h"

void lsp::request::workspace_symbol::from_json(const nlohmann::json &j, params &p) {
  p.query = j.at("query").get<std::string>();
}