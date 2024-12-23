#include "protocol/request/text_document_change.h"

namespace lsp::request::text_document_change {

void from_json(const nlohmann::json &j, params &p) {
  j["textDocument"].get_to(p.text_document);
  j["contentChanges"].get_to(p.content_changes);
}

void from_json(const nlohmann::json &j, change_event &ev) {
  j["text"].get_to(ev.text);
}
} // namespace lsp::request::text_document_change
