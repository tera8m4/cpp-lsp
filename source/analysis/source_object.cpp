#include "analysis/cpp_parser.h"
#include "analysis/source_object.h"
#include "query.h"

source_object::source_object(std::filesystem::path in_path,
                             std::string in_content)
    : path{std::move(in_path)}, content(std::move(in_content)),
      tree{cpp_parser::get_instance().parse(content)} {}

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
      std::string_view class_name = std::string_view{content}.substr(
          range.start, range.end - range.start);

      result.emplace_back(
          class_name, language::location{.file = path, .line = 0, .column = 0});
    }
  }

  return result;
}
