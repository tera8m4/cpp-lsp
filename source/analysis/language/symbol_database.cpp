#include "analysis/symbol_database.h"

void symbol_database::add_declarations(std::vector<language::class_declaration> in_declarations) {
  for (const auto &x : in_declarations) {
    declarations.push_back(x);
  }
}

std::vector<const language::class_declaration *> symbol_database::lookup_declaration(std::string_view key) const {
  std::vector<const language::class_declaration *> result;
  std::string lower_key;
  lower_key.resize(key.size());
  std::transform(key.begin(), key.end(), lower_key.begin(),
    [](unsigned char c){ return std::tolower(c); });

  for (const auto &x : declarations) {
    const std::string_view name = x.get_name();
    std::string lower_name;
    lower_name.resize(name.size());
    std::transform(name.begin(), name.end(), lower_name.begin(),
      [](unsigned char c){ return std::tolower(c); });

    if (lower_name.contains(lower_key)) {
      result.push_back(&x);
    }
  }

  return result;
}
