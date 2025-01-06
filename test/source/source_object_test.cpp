#include <analysis/source_object.h>
#include <doctest/doctest.h>
#include <filesystem>
#include <tree.h>

TEST_CASE("Source objecrt test") {
  std::filesystem::path path{"/tmp/1.cpp"};
  std::string content = "class Foo {}; struct Boo {};";

  source_object obj{path, content};
  const auto &classes = obj.get_classes();
  REQUIRE(classes.size() == 2);
  REQUIRE(classes[0].get_name() == "Foo");
  REQUIRE(classes[1].get_name() == "Boo");
}
