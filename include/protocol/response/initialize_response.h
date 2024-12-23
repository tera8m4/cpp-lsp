#include "response.h"
#include <nlohmann/json.hpp>

namespace lsp::response::initialize {

enum class text_document_sync_type : int {
  none = 0,
  full = 1,
  incremental = 2
};

struct server_capabilities {
  text_document_sync_type text_document_sync = text_document_sync_type::none;
  bool hover_provider{false};
};

struct server_info_t {
  std::string name;
  std::string version;
};

struct result : public base_result {
  server_capabilities capabilities;
  server_info_t server_info;

  void to_json(nlohmann::json &j) const override;
};

void to_json(nlohmann::json &j, const server_capabilities &capabilities);

} // namespace lsp::response::initialize
