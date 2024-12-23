#include "protocol/position.h"

void lsp::from_json(const nlohmann::json &j, lsp::document_position &p) {
  j["line"].get_to(p.line);
  j["character"].get_to(p.character);
}
