#include "protocol/request/text_document_hover.h"
#include "utils.h"

namespace lsp::request::text_document_hover {
void from_json(const nlohmann::json &j, params &p) {
  j["position"].get_to(p.position);
  p.uri = utils::uri2path(j["textDocument"]["uri"].get<std::string>());
}
} // namespace lsp::request::text_document_hover
