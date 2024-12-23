#include "protocol/request/initialize_params.h"
#include "protocol/request/request_parser.h"
#include "protocol/request/text_document_change.h"
#include "protocol/request/text_document_open.h"
#include <nlohmann/json.hpp>

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
    req.params = std::make_unique<initialize::params>(
        data["params"].get<initialize::params>());
    break;

  case request_method::text_document_did_open:
    req.params = std::make_unique<text_document_open::params>(
        data["params"].get<text_document_open::params>());
    break;

  case request_method::text_document_did_change:
    req.params = std::make_unique<text_document_change::params>(
        data["params"].get<text_document_change::params>());
    break;

  case request_method::initialized:
    break;

  default:
    break;
  }
  return req;
}
