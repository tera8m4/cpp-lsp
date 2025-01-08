#include "protocol/request/request.h"
#include "protocol/response/hover_response.h"
#include "protocol/response/initialize_response.h"
#include "protocol/response/response.h"
#include "protocol/response/response_factory.h"
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

  return res;
}

std::unique_ptr<base_result> create_hover_result() {
  using namespace lsp::response::hover;

  auto res = std::make_unique<result>();
  res->contents = "hello from *mylsp*!";

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
  case request_method::initialized:
    break;
  default:
    spdlog::info("failed to create response for {0}",
                 to_string(in_request.method));
    break;
  }

  return {.id = in_request.id, .result = std::move(result)};
}
