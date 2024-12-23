#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>

namespace lsp {
struct version_text_document {
  int version = -1;
  std::filesystem::path uri;
};

void from_json(const nlohmann::json &j, version_text_document &d);
} // namespace lsp
