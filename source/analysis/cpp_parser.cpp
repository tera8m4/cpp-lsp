#include "analysis/cpp_parser.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string_view>
#include <vector>

extern "C" {
TSLanguage *tree_sitter_cpp();
}

cpp_parser &cpp_parser::get_instance() {
  static cpp_parser instance;
  return instance;
}

std::string cleanString(std::string_view input) {
  static std::vector<std::string> skipline = {
      "ENUM_CLASS_FLAGS", "UFUNCTION",      "UENUM",
      "UCLASS",           "UINTERFACE",     "USTRUCT",
      "UPROPERTY",        "GENERATED_BODY", "DECLARE_"};

  for (const auto &x : skipline) {
    if (input.contains(x)) {
      return std::string(input.size(), ' ');
    }
  }

  std::string result(input);

  // Define patterns to replace with spaces
  static std::vector<std::regex> patterns = {
      std::regex(R"([A-Z]+_API)"),  // ENGINE_API, CORE_API, etc.
      std::regex(R"(FORCEINLINE)"), // FORCEINLINE
      std::regex(R"(UMETA\(.*\))"), std::regex(R"(UE_DEPRECATED\(.*\))")};

  // Replace each pattern with spaces
  for (std::size_t i = 0; i < patterns.size(); i++) {
    const auto &pattern = patterns[i];
    std::smatch match;
    while (std::regex_search(result, match, pattern)) {
      size_t pos = match.position();
      size_t len = match.length();
      result.replace(pos, len, std::string(len, ' '));
    }
  }

  return result;
}

auto sanitize(std::string_view source) {

  std::stringstream ss;
  auto lines = std::views::split(source, std::string_view{"\n"}) |
               std::views::transform([](auto &&range) {
                 return std::string_view(range.begin(), range.end());
               });

  std::vector<std::pair<int, int>> offsets;
  std::vector<std::string_view> sanitized_line;
  std::string stantizied_line;

  for (const auto &line : lines) {
    ss << cleanString(line) << '\n';
  }

  return ss.str();
}

cpp_parser::cpp_parser() : language{tree_sitter_cpp()}, parser{language} {}

ts::Tree cpp_parser::parse(std::string_view source_code) {
  try {
    std::string santized_code = sanitize(source_code);
    return parser.parseString(santized_code);
  } catch (const std::exception &e) {
    spdlog::info("Parsing error: {}", e.what());
    return parser.parseString("");
  }
}
