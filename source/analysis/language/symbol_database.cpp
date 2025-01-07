#include "analysis/symbol_database.h"

void symbol_database::add_declarations(std::vector<language::class_declaration> in_declarations) {
  for (const auto &x : in_declarations) {
    declarations.push_back(x);
  }
}

std::vector<const language::class_declaration *> symbol_database::lookup_declaration(std::string_view key) const {
  std::vector<const language::class_declaration *> result;
  for (const auto &x : declarations) {
    if (x.get_name().contains(key)) {
      result.push_back(&x);
    }
  }

  return result;
}
