#include "response.h"
#include <nlohmann/json.hpp>

namespace lsp::response::initialize {
struct server_capabilities {};
struct server_info_t {
  std::string name;
  std::string version;
};

struct result : public base_result {
  server_capabilities capabilities;
  server_info_t server_info;

  void to_json(nlohmann::json &j) const override;
};

} // namespace lsp::response::initialize
