#include "analysis/cpp_parser.h"


#include <string_view>
#include <ranges>
#include <iostream>
#include <vector>

extern "C" {
TSLanguage *tree_sitter_cpp_ue5();
}

cpp_parser &cpp_parser::get_instance() {
  static cpp_parser instance;
  return instance;
}

bool is_forward_declaration(std::string_view line) {
  return (line.starts_with("class") || line.starts_with("struct")) && line.ends_with(';');
}

bool predicate(std::string_view line) {
    // Trim whitespace
    while (!line.empty() && std::isspace(line.front())) line.remove_prefix(1);
    while (!line.empty() && std::isspace(line.back())) line.remove_suffix(1);
 
  return !line.contains("UPROPERTY") && !line.contains("UFUNCTION") 
  && !line.contains("UCLASS") && !line.contains("USTRUCT") && !line.contains("GENERATED_BODY")
  && !line.contains("UENUM") && !line.contains("UE_DEPRECATED") && !line.contains("ENUM_CLASS_FLAGS")
  && !line.contains("DECLARE_") && !is_forward_declaration(line);
}

std::string sanitize(std::string_view source) {

 
  return std::views::split(source, std::string_view{"\n"}) 
         | std::views::transform([](auto&& range) {
               return std::string_view(range.begin(), range.end());
           })
        | std::views::filter([](auto&& line) {
                             return predicate(line);
                             })
        | std::views::join_with('\n')
      | std::ranges::to<std::string>();
}

cpp_parser::cpp_parser() : language{tree_sitter_cpp_ue5()}, parser{language} {}

ts::Tree cpp_parser::parse(std::string_view source_code) {
  std::string santized_code = sanitize(source_code);


  return parser.parseString(source_code);
}
