#include <doctest/doctest.h>
#include <format>
#include <protocol/request/initialize_params.h>
#include <protocol/request/request_parser.h>
#include <protocol/request/text_document_open.h>
#include <protocol/text_document_item.h>
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

TEST_CASE("parser textDocument/DidOpen") {
  SUBCASE("from_json correctly parses JSON into text_document_item") {
    nlohmann::json j = {{"languageId", "cpp"},
                        {"version", 1},
                        {"text", "int main() { return 0; }"},
                        {"uri", "file:///home/user/main.cpp"}};

    lsp::text_document_item item = j.get<lsp::text_document_item>();

    CHECK(item.language_id == "cpp");
    CHECK(item.version == 1);
    CHECK(item.text == "int main() { return 0; }");
    CHECK(item.uri == "/home/user/main.cpp");
  }

  SUBCASE("from_json correctly parses JSON into text_document_item") {
    nlohmann::json text_document = {{"languageId", "cpp"},
                                    {"version", 1},
                                    {"text", "int main() { return 0; }"},
                                    {"uri", "file:///home/user/main.cpp"}};

    nlohmann::json j = {{"textDocument", text_document}};
    lsp::request::text_document_open::params document_open =
        j.get<lsp::request::text_document_open::params>();

    const auto &item = document_open.text_document;

    CHECK(item.language_id == "cpp");
    CHECK(item.version == 1);
    CHECK(item.text == "int main() { return 0; }");
    CHECK(item.uri == "/home/user/main.cpp");
  }
}
