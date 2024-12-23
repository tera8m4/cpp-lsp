#pragma once

#include "response.h"
#include <string>

namespace lsp::response::hover {
struct result : public base_result {
  std::string contents;
  void to_json(nlohmann::json &j) const override;
};
} // namespace lsp::response::hover
