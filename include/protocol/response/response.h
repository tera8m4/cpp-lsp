#pragma once

#include <memory>
#include <nlohmann/json.hpp>

struct base_result {
  virtual void to_json(nlohmann::json &j) const = 0;
  virtual ~base_result() = default;
};

struct response_message {
  int id = -1;
  std::unique_ptr<base_result> result{};
};

void to_json(nlohmann::json &j, const response_message &in_response);
void to_json(nlohmann::json &j, const base_result &in_result);
