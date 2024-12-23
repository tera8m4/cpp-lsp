#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "protocol/version_text_document.h"
#include "request.h"

namespace lsp::request::text_document_change {
struct change_event {
  std::string text;
};

struct params : public base_params {
  version_text_document text_document;
  std::vector<change_event> content_changes;
};

void from_json(const nlohmann::json &j, change_event &ev);
void from_json(const nlohmann::json &j, params &p);
} // namespace lsp::request::text_document_change
