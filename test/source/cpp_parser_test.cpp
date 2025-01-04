#include <analysis/cpp_parser.h>
#include <doctest/doctest.h>
#include <tree.h>

TEST_CASE("cpp_parser::parse") {
  auto &parser = cpp_parser::get_instance();
  const std::string_view source = "int main() { return 0; }";
  ts::Tree tree = parser.parse(source);

  CHECK(!tree.hasError());
}
