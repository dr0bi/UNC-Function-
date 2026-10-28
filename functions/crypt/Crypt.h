#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace unc::crypt_api {

// Portable Base64 helpers. These operate on bytes and do not perform encryption.
[[nodiscard]] std::string base64_encode(std::string_view input);
[[nodiscard]] std::optional<std::string> base64_decode(std::string_view input);

} // namespace unc::crypt_api
