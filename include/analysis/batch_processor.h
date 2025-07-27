#pragma once

#include "directory_crawler.h"
#include "symbol_database.h"
#include <filesystem>
#include <vector>

namespace analysis {

class batch_processor {
public:
  void process_directories(const std::vector<std::filesystem::path>& directories, 
                          symbol_database& database);

private:
  directory_crawler crawler;
  
  void process_file(const std::filesystem::path& file_path, symbol_database& database);
  std::string read_file(const std::filesystem::path& path) const;
};

} // namespace analysis
