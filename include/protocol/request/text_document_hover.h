#pragma once
#include "protocol/position.h"
#include "request.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace lsp::request::text_document_hover {
struct params : public base_params {
  std::filesystem::path uri;
  document_position position;
};

void from_json(const nlohmann::json &j, params &p);
} // namespace lsp::request::text_document_hover
