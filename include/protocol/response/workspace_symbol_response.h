#pragma once
#include "response.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace lsp::response::workspace_symbol {

enum class symbol_kind : int {
  file = 1,
  module = 2,
  namespace_ = 3,
  package = 4,
  class_ = 5,
  method = 6,
  property = 7,
  field = 8,
  constructor = 9,
  enum_ = 10,
  interface = 11,
  function = 12,
  variable = 13,
  constant = 14
};

struct location {
  std::string uri;
  struct range_type {
    struct position {
      int line;
      int character;
    } start, end;
  } range;
};

struct symbol_information {
  std::string name;
  symbol_kind kind;
  location location_;
  std::string container_name;
};

struct result : public base_result {
  std::vector<symbol_information> symbols;
  
  void to_json(nlohmann::json &j) const override;
};

void to_json(nlohmann::json &j, const symbol_information &s);
void to_json(nlohmann::json &j, const location &l);
void to_json(nlohmann::json &j, const location::range_type &r);
void to_json(nlohmann::json &j, const location::range_type::position &p);

} // namespace lsp::response::workspace_symbol
