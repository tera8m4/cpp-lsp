#pragma once

#include "language/class_declaration.h"
#include <string_view>
#include <vector>

class symbol_database {
public:
  void add_declarations(std::vector<language::class_declaration> in_declarations);
  std::vector<const language::class_declaration *> lookup_declaration(std::string_view key) const;

private:
  std::vector<language::class_declaration> declarations;
};
