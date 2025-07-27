#pragma once

#include "batch_processor.h"
#include "symbol_database.h"
#include <filesystem>
#include <vector>

namespace analysis {

class ue_parser {
public:
  void parse_unreal_source(const std::vector<std::filesystem::path>& directories, 
                          symbol_database& database);
  
private:
  batch_processor processor;
};

} // namespace analysis
