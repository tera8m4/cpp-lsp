#include "analysis/cpp_parser.h"

extern "C" {
TSLanguage *tree_sitter_cpp();
}

cpp_parser &cpp_parser::get_instance() {
  static cpp_parser instance;
  return instance;
}

cpp_parser::cpp_parser() : language{tree_sitter_cpp()}, parser{language} {}

ts::Tree cpp_parser::parse(std::string_view source_code) {
  return parser.parseString(source_code);
}
