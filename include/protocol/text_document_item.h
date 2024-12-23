#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

namespace lsp {
struct text_document_item {
  std::filesystem::path uri;
  std::string language_id;
  int version = -1;
  std::string text;
};

void from_json(const nlohmann::json &j, text_document_item &item);
} // namespace lsp
