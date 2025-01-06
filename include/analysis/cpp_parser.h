#pragma once

#include <language.h>
#include <parser.h>
#include <string_view>
#include <tree.h>

class cpp_parser {
public:
  static cpp_parser &get_instance();
  ts::Tree parse(std::string_view source_code);

private:
  cpp_parser();
  ts::Language language;
  ts::Parser parser;
};
