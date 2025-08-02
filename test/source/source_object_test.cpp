#include <analysis/source_object.h>
#include <doctest/doctest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tree.h>

std::string read_file_to_string(const std::filesystem::path &file_path) {
  std::ifstream file(file_path);
  if (!file) {
    throw std::runtime_error("Cannot open file: " + file_path.string());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

TEST_CASE("Source objecrt test") {
  std::filesystem::path path{"/tmp/1.cpp"};
  std::string content = "class Foo {}; struct Boo {};";

  source_object obj{path, content};
  const auto &classes = obj.get_classes();
  REQUIRE(classes.size() == 2);
  REQUIRE(classes[0].get_name() == "Foo");
  REQUIRE(classes[1].get_name() == "Boo");
}

TEST_CASE("Source objecrt test 2") {
  std::filesystem::path path{"/home/tera8/ue/Engine/Source/Runtime/Engine/"
                             "Classes/GameFramework/Actor.h"};
  std::string content = read_file_to_string(path);

  source_object obj{path, content};
  const auto &classes = obj.get_classes();
  REQUIRE(classes.size() == 2);
  REQUIRE(classes[0].get_name() == "Foo");
  REQUIRE(classes[1].get_name() == "Boo");
}
