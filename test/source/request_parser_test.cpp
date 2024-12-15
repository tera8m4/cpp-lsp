#include <doctest/doctest.h>
#include <format>
#include <protocol/request/initialize_params.h>
#include <protocol/request/request_parser.h>
#include <string>
#include <string_view>

TEST_CASE("parser initailize request") {
  constexpr std::string_view request_format =
      R"({{ "id": 1, "method": "{0}", "params": {1}}})";

  constexpr std::string_view params_str =
      R"({ "clientInfo": { "name": "my-client", "version": "1.0.0-alpha" } })";
  constexpr std::string_view method_name = "initialize";

  SUBCASE("request with valid data") {
    using params = lsp::request::initialize::params;

    const auto request_message =
        std::format(request_format, method_name, params_str);

    auto request = request_parser::parse(request_message);
    CHECK(request.method == request_method::initialize);

    auto &request_params = *dynamic_cast<params *>(request.params.get());
    CHECK(request_params.client_info->name == "my-client");
    CHECK(request_params.client_info->version == "1.0.0-alpha");
  }
}
