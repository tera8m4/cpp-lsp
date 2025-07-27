#include "protocol/request/initialize_params.h"
#include "protocol/request/request_parser.h"
#include "protocol/request/text_document_change.h"
#include "protocol/request/text_document_hover.h"
#include "protocol/request/text_document_open.h"
#include "protocol/request/workspace_symbol.h"
#include <nlohmann/json.hpp>

namespace {
template <typename T> std::unique_ptr<T> parse_params(const auto &j) {
  static_assert(std::derived_from<T, base_params>);
  return std::make_unique<T>(j["params"].template get<T>());
}
} // namespace

request request_parser::parse(const std::string_view request_message) {
  using json = nlohmann::json;

  json data = json::parse(request_message);
  const std::string &method = data["method"].get<std::string>();

  const int id = data.value("id", -1);

  // the cast seems not safe
  request req{.id = id,
              .method = static_cast<request_method>(string_to_uint(method))};

  using namespace lsp::request;
  switch (req.method) {
  case request_method::initialize:
    req.params = parse_params<initialize::params>(data);
    break;

  case request_method::text_document_did_open:
    req.params = parse_params<text_document_open::params>(data);
    break;

  case request_method::text_document_did_change:
    req.params = parse_params<text_document_change::params>(data);
    break;

  case request_method::text_document_hover:
    req.params = parse_params<text_document_hover::params>(data);
    break;

  case request_method::workspace_symbol:
    req.params = parse_params<workspace_symbol::params>(data);
    break;

  case request_method::initialized:
    break;

  default:
    break;
  }
  return req;
}
