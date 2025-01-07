#include <analysis/language/class_declaration.h>
#include <analysis/symbol_database.h>
#include <doctest/doctest.h>
#include <filesystem>
#include <string_view>
#include <vector>

TEST_CASE("cpp_parser::parse") {
  using namespace std::literals;
  symbol_database db;

  std::vector<language::class_declaration> declarations;
  declarations.emplace_back("ClassA"sv, language::location{std::filesystem::path{"/src/ClassA.cpp"}, 10, 15});
  declarations.emplace_back("ClassB"sv, language::location{std::filesystem::path{"/src/ClassB.cpp"}, 10, 15});
  declarations.emplace_back("ClassC"sv, language::location{std::filesystem::path{"/src/ClassC.cpp"}, 10, 15});
  declarations.emplace_back("ClassD"sv, language::location{std::filesystem::path{"/src/ClassD.cpp"}, 10, 15});
  declarations.emplace_back("ClassE"sv, language::location{std::filesystem::path{"/src/ClassE.cpp"}, 10, 15});

  db.add_declarations(std::move(declarations));

  const auto &found_declarations = db.lookup_declaration("Class");
  REQUIRE(found_declarations.size() == 5);

  const auto &single_declaration = db.lookup_declaration("A");
  REQUIRE(single_declaration.size() == 1);

  REQUIRE(db.lookup_declaration("foo").size() == 0);
}
