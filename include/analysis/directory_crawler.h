#pragma once

#include <filesystem>
#include <vector>

namespace analysis {

class directory_crawler {
public:
  std::vector<std::filesystem::path> find_header_files(const std::vector<std::filesystem::path>& directories) const;

private:
  bool is_header_file(const std::filesystem::path& path) const;
  void crawl_directory_recursive(const std::filesystem::path& directory, 
                                std::vector<std::filesystem::path>& result) const;
};

} // namespace analysis
