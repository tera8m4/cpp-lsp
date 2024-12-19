#include <doctest/doctest.h>
#include <format>
#include <protocol/request/initialize_params.h>
#include <protocol/request/request_parser.h>
#include <protocol/response/initialize_response.h>
#include <protocol/response/response_factory.h>
#include <string>
#include <string_view>

TEST_CASE("response to initailize request") {
  const std::string_view initailize_request =
      R"({ "id": 331, "method": "initialize", "params": { "clientInfo": { "name": "my-client", "version": "1.0.0-alpha" } } })";
  const request req = request_parser::parse(initailize_request);

  response_factory factory;
  auto resp = factory.create(req);

  CHECK(resp.id == 331);

  auto *result =
      dynamic_cast<lsp::response::initialize::result *>(resp.result.get());
  CHECK(result != nullptr);
  CHECK(result->server_info.version == "0.0.1-alpha");

  SUBCASE("initialize response converts to json") {
    nlohmann::json response_json = resp;
    CHECK(response_json["result"]["serverInfo"]["version"].get<std::string>() ==
          "0.0.1-alpha");
    CHECK(response_json["jsonrpc"].get<std::string>() == "2.0");
    CHECK(response_json["result"]["capabilities"].is_object());
  }
}
