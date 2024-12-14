#include <doctest/doctest.h>
#include <sstream>
#include <transport/transport.h>

TEST_CASE("transport parsing operations") {

  SUBCASE("parse small valid message") {
    std::istringstream input("Content-Length: 2\r\n\r\n{}");
    std::string result = transport::read_message(input);
    CHECK(result == "{}");
  }

  SUBCASE("Valid input with correct Content-Length header") {
    std::istringstream input("Content-Length: 15\r\n\r\n{\"key\":\"value\"}");
    std::string expected = "{\"key\":\"value\"}";
    CHECK(transport::read_message(input) == expected);
  }

  SUBCASE("Invalid input with missing Content-Length header") {
    std::istringstream input("\r\n{\"key\":\"value\"}");
    CHECK(transport::read_message(input).size() == 0);
  }

  SUBCASE("Invalid input with zero Content-Length") {
    std::istringstream input("Content-Length: 0\r\n\r\n");
    CHECK(transport::read_message(input).size() == 0);
  }

  SUBCASE("Multiline JSON content") {
    std::istringstream input(
        "Content-Length: 35\r\n\r\n{\"key1\":\"value1\",\n\"key2\": "
        "\"value2\"}");
    std::string expected = "{\"key1\":\"value1\",\n\"key2\": \"value2\"}";
    std::string actual = transport::read_message(input);
    CHECK(actual == expected);
  }
}
