#include "protocol/response/initialize_response.h"

namespace lsp::response::initialize {
using json = nlohmann::json;
void result::to_json(json &j) const {
  j = json{{"capabilities", {}},
           {"serverInfo",
            {{"name", server_info.name}, {"version", server_info.version}}}};
}
} // namespace lsp::response::initialize
