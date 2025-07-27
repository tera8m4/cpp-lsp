#include "protocol/request/request.h"
#include "protocol/response/hover_response.h"
#include "protocol/response/initialize_response.h"
#include "protocol/response/response.h"
#include "protocol/response/response_factory.h"
#include "protocol/response/workspace_symbol_response.h"
#include <cstdint>
#include <spdlog/spdlog.h>

namespace {
std::unique_ptr<base_result> create_initalize_result() {
  using namespace lsp::response::initialize;

  auto res = std::make_unique<result>();
  res->server_info.name = "my-cpp-lsp";
  res->server_info.version = "0.0.1-alpha";
  res->capabilities.text_document_sync = text_document_sync_type::full;
  res->capabilities.hover_provider = true;
  res->capabilities.workspace_symbol_provider = true;

  return res;
}

std::unique_ptr<base_result> create_hover_result() {
  using namespace lsp::response::hover;

  auto res = std::make_unique<result>();
  res->contents = "hello from *mylsp*!";

  return res;
}

std::unique_ptr<base_result> create_workspace_symbol_result() {
  using namespace lsp::response::workspace_symbol;

  auto res = std::make_unique<result>();
  
  symbol_information sym1;
  sym1.name = "MyClass";
  sym1.kind = symbol_kind::class_;
  sym1.location_.uri = "file:///tmp/1.cpp";
  sym1.location_.range.start = {10, 0};
  sym1.location_.range.end = {20, 0};
  sym1.container_name = "";
  
  symbol_information sym2;
  sym2.name = "myFunction";
  sym2.kind = symbol_kind::function;
  sym2.location_.uri = "file:///tmp/1.cpp";
  sym2.location_.range.start = {25, 4};
  sym2.location_.range.end = {30, 5};
  sym2.container_name = "MyClass";
  
  res->symbols = {sym1, sym2};
  return res;
}
} // namespace

response_message response_factory::create(const request &in_request) const {
  std::unique_ptr<base_result> result;
  switch (in_request.method) {
  case request_method::initialize: {
    result = create_initalize_result();
  } break;

  case request_method::text_document_hover:
    result = create_hover_result();
    break;
  case request_method::workspace_symbol:
    result = create_workspace_symbol_result();
    break;
  case request_method::initialized:
    break;
  default:
    spdlog::info("failed to create response for {0}",
                 to_string(in_request.method));
    break;
  }

  return {.id = in_request.id, .result = std::move(result)};
}
