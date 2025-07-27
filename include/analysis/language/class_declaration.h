#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

namespace language {

struct location {
  std::filesystem::path file;
  int line = 0;
  int column = 0;
};

class class_declaration {
public:
  explicit class_declaration(std::string_view in_name, location in_loc);
  std::string_view get_name() const;
  const location &get_location() const;

private:
  std::string name;
  location loc;
};
} // namespace language
