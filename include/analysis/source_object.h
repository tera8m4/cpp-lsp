#pragma once
#include <filesystem>
#include <string>
#include <tree.h>
#include <vector>

#include "language/class_declaration.h"

class source_object {
public:
  explicit source_object(std::filesystem::path in_path, std::string in_content);

  std::vector<language::class_declaration> get_classes() const;

private:
  std::filesystem::path path;
  std::string content;
  ts::Tree tree;
};
