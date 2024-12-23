#include "protocol/request/text_document_open.h"
namespace lsp::request::text_document_open {
void from_json(const nlohmann::json &j, params &p) {
  p.text_document = j["textDocument"].get<lsp::text_document_item>();
}
} // namespace lsp::request::text_document_open
