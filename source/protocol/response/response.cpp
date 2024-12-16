#include "protocol/response/response.h"

void to_json(nlohmann::json &j, const response_message &in_response) {
  using nlohmann::json;
  j = json{{"jsonrpc", "2.0"}, {"id", in_response.id}};
  if (in_response.result != nullptr) {
    j["result"] = *in_response.result;
  }
}

void to_json(nlohmann::json &j, const base_result &in_result) {
  in_result.to_json(j);
}
