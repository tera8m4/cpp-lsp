#include <doctest/doctest.h>
#include <utils.h>

TEST_CASE("utils::uri2path") {
  SUBCASE("Valid file URI on POSIX") {
    CHECK(utils::uri2path("file:///home/user/test%20file.txt") ==
          "/home/user/test file.txt");
  }

  SUBCASE("Valid file URI on Windows with drive letter") {
    CHECK(utils::uri2path("file:///C:/path/to/some%20file.txt") ==
          "C:/path/to/some file.txt");
  }

  SUBCASE("Valid file URI on Windows without encoding") {
    CHECK(utils::uri2path("file:///C:/path/to/file.txt") ==
          "C:/path/to/file.txt");
  }

  SUBCASE("Invalid file URI without file:// prefix") {
    CHECK(utils::uri2path("http://example.com/path/to/file.txt").empty());
  }

  SUBCASE("Invalid file URI with malformed percent encoding") {
    CHECK(utils::uri2path("file:///path/to/invalid%XYfile.txt").empty());
  }

  SUBCASE("File URI with plus signs interpreted as spaces") {
    CHECK(utils::uri2path("file:///path/with+spaces") == "/path/with spaces");
  }
}
