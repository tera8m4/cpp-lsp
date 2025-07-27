#include "protocol/response/workspace_symbol_response.h"

void lsp::response::workspace_symbol::to_json(nlohmann::json &j, const location::range_type::position &p) {
  j = nlohmann::json{{"line", p.line}, {"character", p.character}};
}

void lsp::response::workspace_symbol::to_json(nlohmann::json &j, const location::range_type &r) {
  j = nlohmann::json{{"start", r.start}, {"end", r.end}};
}

void lsp::response::workspace_symbol::to_json(nlohmann::json &j, const location &l) {
  j = nlohmann::json{{"uri", l.uri}, {"range", l.range}};
}

void lsp::response::workspace_symbol::to_json(nlohmann::json &j, const symbol_information &s) {
  j = nlohmann::json{
    {"name", s.name},
    {"kind", static_cast<int>(s.kind)},
    {"location", s.location_},
    {"containerName", s.container_name}
  };
}

void lsp::response::workspace_symbol::result::to_json(nlohmann::json &j) const {
  j = nlohmann::json(symbols);
}
