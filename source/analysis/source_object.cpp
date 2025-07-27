#include "analysis/cpp_parser.h"
#include "analysis/source_object.h"
#include "query.h"

source_object::source_object(std::filesystem::path in_path,
                             std::string in_content)
    : path{std::move(in_path)}, content(std::move(in_content)),
      tree{cpp_parser::get_instance().parse(content)} {}

std::pair<int, int> byteOffsetToLineColumn(const std::string_view text, const std::size_t byteOffset) {
    int line = 0;
    int column = 0;
    
    for (std::size_t i = 0; i < byteOffset && i < text.size(); i++) {
        if (text[i] == '\n') {
            line++;
            column = 0;
        } else {
            column++;
        }
    }
    
    return { line, column };
}

std::vector<language::class_declaration> source_object::get_classes() const {
  const std::string_view class_name_query_source =
      "[(class_specifier name: (type_identifier) @name)"
      "(struct_specifier name: (type_identifier) @name)]";

  ts::Query class_name_query{tree.getLanguage(), class_name_query_source};
  ts::Node root = tree.getRootNode();
  ts::QueryCursor cursor = class_name_query.exec(root);

  std::vector<language::class_declaration> result;

  for (const ts::QueryMatch &match : cursor) {
    for (const auto &capture : match.getCaptures()) {
      const auto range = capture.getNode().getByteRange();
      
      if (range.start >= content.size() || range.end > content.size() || range.start >= range.end) {
        continue;
      }
      
      std::string_view class_name = std::string_view{content}.substr(
          range.start, range.end - range.start);
      
      // Skip if the extracted name is empty or contains null bytes
      if (class_name.empty() || class_name.find('\0') != std::string_view::npos) {
        continue;
      }

      auto start_point = byteOffsetToLineColumn(content, range.start);
      result.emplace_back(
          class_name, language::location{.file = path, .line = start_point.first, .column = start_point.second });
    }
  }

  return result;
}
