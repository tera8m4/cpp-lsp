#include <doctest/doctest.h>
#include <format>
#include <protocol/request/initialize_params.h>
#include <protocol/request/request_parser.h>
#include <protocol/response/hover_response.h>
#include <protocol/response/initialize_response.h>
#include <protocol/response/response_factory.h>
#include <protocol/response/workspace_symbol_response.h>
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
    CHECK(response_json["result"]["capabilities"]["textDocumentSync"]
              .is_number_integer());
  }
}

TEST_CASE("hover response") {
  const std::string hover_message = R"({ 
    "id": 1, 
    "method": "textDocument/hover",
    "params": { "textDocument": { "uri": "file:///1.txt" }, "position": { "line": 100, "character": 22 }}                                   
  })";

  const auto &req = request_parser::parse(hover_message);
  response_factory factory;
  auto resp = factory.create(req);
  CHECK(resp.id == 1);
  auto &result = dynamic_cast<lsp::response::hover::result &>(*resp.result);

  CHECK(result.contents.size() > 0);
}

TEST_CASE("workspace symbol response") {
  const std::string workspace_symbol_message = R"({ 
    "id": 3, 
    "method": "workspace/symbol",
    "params": { "query": "MyClass" }                                   
  })";

  const auto &req = request_parser::parse(workspace_symbol_message);
  response_factory factory;
  auto resp = factory.create(req);
  
  CHECK(resp.id == 3);
  auto &result = dynamic_cast<lsp::response::workspace_symbol::result &>(*resp.result);
  CHECK(result.symbols.size() == 2);
  CHECK(result.symbols[0].name == "MyClass");
  CHECK(result.symbols[0].kind == lsp::response::workspace_symbol::symbol_kind::class_);
  CHECK(result.symbols[1].name == "myFunction");
  CHECK(result.symbols[1].kind == lsp::response::workspace_symbol::symbol_kind::function);
  
  SUBCASE("workspace symbol response converts to json") {
    nlohmann::json response_json = resp;
    CHECK(response_json["result"]["symbols"].is_array());
    CHECK(response_json["result"]["symbols"].size() == 2);
    CHECK(response_json["result"]["symbols"][0]["name"].get<std::string>() == "MyClass");
    CHECK(response_json["result"]["symbols"][0]["kind"].get<int>() == 5);
    CHECK(response_json["result"]["symbols"][0]["location"]["uri"].get<std::string>() == "file:///example.cpp");
    CHECK(response_json["result"]["symbols"][1]["containerName"].get<std::string>() == "MyClass");
  }
}
