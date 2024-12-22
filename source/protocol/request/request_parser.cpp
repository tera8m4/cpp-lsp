#include "protocol/request/initialize_params.h"
#include "protocol/request/request_parser.h"
#include <nlohmann/json.hpp>

request request_parser::parse(const std::string_view request_message) {
  using json = nlohmann::json;

  json data = json::parse(request_message);
  const std::string &method = data["method"].get<std::string>();

  const int id = data.value("id", -1);

  // the cast seems not safe
  request req{.id = id,
              .method = static_cast<request_method>(string_to_uint(method))};

  if (req.method == request_method::initialize) {
    using namespace lsp::request;
    req.params = std::make_unique<initialize::params>(
        data["params"].get<initialize::params>());
  }
  return req;
}
