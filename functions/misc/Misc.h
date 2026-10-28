#pragma once
#include <string>
#include <string_view>
#include <vector>
namespace unc::misc_api {
[[nodiscard]] std::string trim(std::string_view value);
[[nodiscard]] std::vector<std::string> split(std::string_view value, char delimiter, bool keep_empty = true);
[[nodiscard]] bool starts_with(std::string_view value, std::string_view prefix) noexcept;
[[nodiscard]] bool ends_with(std::string_view value, std::string_view suffix) noexcept;
[[nodiscard]] std::string replace_all(std::string_view value, std::string_view needle, std::string_view replacement);
} // namespace unc::misc_api
