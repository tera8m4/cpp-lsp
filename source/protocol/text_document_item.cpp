#include "protocol/text_document_item.h"
#include "utils.h"

namespace lsp {
void from_json(const nlohmann::json &j, text_document_item &item) {
  item.language_id = j["languageId"].get<std::string>();
  item.version = j["version"].get<int>();
  item.text = j["text"].get<std::string>();
  item.uri = utils::uri2path(j["uri"].get<std::string>());
}
} // namespace lsp
