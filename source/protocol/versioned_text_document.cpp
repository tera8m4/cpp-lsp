#include "protocol/version_text_document.h"
#include "utils.h"

namespace lsp {
void from_json(const nlohmann::json &j, version_text_document &d) {
  d.version = j["version"].get<int>();
  d.uri = utils::uri2path(j["uri"].get<std::string>());
}
} // namespace lsp
