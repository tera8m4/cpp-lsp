#include "protocol/response/hover_response.h"

namespace lsp::response::hover {
void result::to_json(nlohmann::json &j) const { j["contents"] = contents; }
} // namespace lsp::response::hover
