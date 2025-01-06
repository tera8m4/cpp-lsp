#include "analysis/language/class_declaration.h"

namespace language {
class_declaration::class_declaration(std::string_view in_name, location in_loc)
    : name{in_name}, loc{std::move(in_loc)} {}

std::string_view class_declaration::get_name() const { return name; }
const location &class_declaration::get_location() const { return loc; }

} // namespace language
