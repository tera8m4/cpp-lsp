#include "analysis/ue_parser.h"

namespace analysis {

void ue_parser::parse_unreal_source(const std::vector<std::filesystem::path>& directories, 
                                    symbol_database& database) {
  processor.process_directories(directories, database);
}

} // namespace analysis