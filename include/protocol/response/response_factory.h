#pragma once

#include "response.h"
#include "analysis/symbol_database.h"
#include <memory>

struct request;

class response_factory {
public:
  explicit response_factory(std::shared_ptr<const symbol_database> in_symbols);
  response_message create(const request &in_request) const;

private:
  std::shared_ptr<const symbol_database> symbols;
};
