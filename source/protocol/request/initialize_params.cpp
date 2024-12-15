#include "protocol/request/initialize_params.h"
#include <nlohmann/json.hpp>

namespace lsp::request::initialize {
void from_json(const nlohmann::json &j, lsp::request::initialize::params &p) {
  if (j.contains("clientInfo")) {
    p.client_info = j["clientInfo"].get<client_info_t>();
  }
}

void from_json(const nlohmann::json &j, client_info_t &client_info) {
  j["name"].get_to(client_info.name);
  j["version"].get_to(client_info.version);
}
} // namespace lsp::request::initialize
