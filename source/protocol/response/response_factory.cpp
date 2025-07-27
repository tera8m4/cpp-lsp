#include "protocol/request/request.h"
#include "protocol/request/workspace_symbol.h"
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

std::unique_ptr<base_result> create_workspace_symbol_result(const symbol_database& database, std::string_view query) {
  using namespace lsp::response::workspace_symbol;

  auto res = std::make_unique<result>();
  
  auto declarations = database.lookup_declaration(query);
  
  for (const auto* decl : declarations) {
    symbol_information sym;
    sym.name = std::string(decl->get_name());
    sym.kind = symbol_kind::class_;
    
    const auto& loc = decl->get_location();
    sym.location_.uri = "file://" + loc.file.string();
    sym.location_.range.start = {loc.line, loc.column};
    sym.location_.range.end = {loc.line, loc.column};
    sym.container_name = "";
    
    res->symbols.push_back(sym);
  }
  
  return res;
}
} // namespace

response_factory::response_factory(std::shared_ptr<const symbol_database> in_symbols) : symbols(in_symbols) {}

response_message response_factory::create(const request &in_request) const {
  std::unique_ptr<base_result> result;
  switch (in_request.method) {
  case request_method::initialize: {
    result = create_initalize_result();
  } break;

  case request_method::text_document_hover:
    result = create_hover_result();
    break;
  case request_method::workspace_symbol: {
    auto ws_params = static_cast<const lsp::request::workspace_symbol::params*>(in_request.params.get());
    std::string_view query = ws_params ? ws_params->query : "";
    result = create_workspace_symbol_result(*symbols, query);
    break;
  }
  case request_method::initialized:
    break;
  default:
    spdlog::info("failed to create response for {0}",
                 to_string(in_request.method));
    break;
  }

  return {.id = in_request.id, .result = std::move(result)};
}
