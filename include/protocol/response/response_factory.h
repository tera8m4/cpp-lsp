#pragma once

#include "response.h"

struct request;

class response_factory {
public:
  response_message create(const request &in_request) const;
};
