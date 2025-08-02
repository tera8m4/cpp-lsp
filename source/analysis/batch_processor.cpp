#include "analysis/batch_processor.h"
#include "analysis/source_object.h"
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>

namespace analysis {

void batch_processor::process_directories(
    const std::vector<std::filesystem::path> &directories,
    symbol_database &database) {
  auto header_files = crawler.find_header_files(directories);

  spdlog::info("Found {0} header files to process", header_files.size());

  for (const auto &file_path : header_files) {
    process_file(file_path, database);
  }
}

void batch_processor::process_file(const std::filesystem::path &file_path,
                                   symbol_database &database) {
  std::string content = read_file(file_path);
  if (content.empty()) {
    return;
  }

  source_object source{file_path, std::move(content)};
  auto declarations = source.get_classes();

  database.add_declarations(std::move(declarations));
}

std::string
batch_processor::read_file(const std::filesystem::path &path) const {
  std::ifstream file{path};
  if (!file.is_open()) {
    return {};
  }

  return std::string{std::istreambuf_iterator<char>{file},
                     std::istreambuf_iterator<char>{}};
}

} // namespace analysis
