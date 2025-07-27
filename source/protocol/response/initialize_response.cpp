#include "protocol/response/initialize_response.h"

namespace lsp::response::initialize {
using json = nlohmann::json;
void result::to_json(json &j) const {
  j = json{{"capabilities", capabilities},
           {"serverInfo",
            {{"name", server_info.name}, {"version", server_info.version}}}};
}

void to_json(nlohmann::json &j, const server_capabilities &capabilities) {
  j = json{
      {"textDocumentSync", static_cast<int>(capabilities.text_document_sync)},
      {"hoverProvider", capabilities.hover_provider},
      {"workspaceSymbolProvider", capabilities.workspace_symbol_provider},
  };
}

} // namespace lsp::response::initialize
