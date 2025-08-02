#include "analysis/directory_crawler.h"

namespace analysis {

std::vector<std::filesystem::path> directory_crawler::find_header_files(
    const std::vector<std::filesystem::path> &directories) const {
  std::vector<std::filesystem::path> result;

  for (const auto &directory : directories) {
    if (std::filesystem::exists(directory) &&
        std::filesystem::is_directory(directory)) {
      crawl_directory_recursive(directory, result);
    }
  }

  return result;
}

bool directory_crawler::is_header_file(
    const std::filesystem::path &path) const {
  const auto extension = path.extension().string();
  return extension == ".h" || extension == ".hpp" || extension == ".hxx";
}

void directory_crawler::crawl_directory_recursive(
    const std::filesystem::path &directory,
    std::vector<std::filesystem::path> &result) const {
  try {
    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(directory)) {
      if (entry.is_regular_file() && is_header_file(entry.path())) {
        result.push_back(entry.path());
      }
    }
  } catch (const std::filesystem::filesystem_error &) {
    // Skip directories that can't be accessed
  }
}

} // namespace analysis