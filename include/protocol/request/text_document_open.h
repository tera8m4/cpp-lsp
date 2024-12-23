#pragma once

#include "protocol/request/request.h"
#include "protocol/text_document_item.h"
#include <nlohmann/json.hpp>

namespace lsp::request::text_document_open {
struct params : public base_params {
  text_document_item text_document;
};

void from_json(const nlohmann::json &j, params &p);
} // namespace lsp::request::text_document_open
