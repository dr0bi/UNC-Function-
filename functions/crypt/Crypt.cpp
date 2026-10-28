#include "Crypt.h"

#include <array>
#include <cctype>

namespace unc::crypt_api {
namespace {
constexpr std::string_view alphabet =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

constexpr std::array<signed char, 256> make_decode_table() {
    std::array<signed char, 256> table{};
    for (auto& value : table) value = -1;
    for (std::size_t i = 0; i < alphabet.size(); ++i)
        table[static_cast<unsigned char>(alphabet[i])] = static_cast<signed char>(i);
    return table;
}
constexpr auto decode_table = make_decode_table();
}

std::string base64_encode(std::string_view input) {
    std::string output;
    output.reserve(((input.size() + 2) / 3) * 4);
    unsigned int buffer = 0;
    int bits = -6;
    for (unsigned char byte : input) {
        buffer = (buffer << 8) | byte;
        bits += 8;
        while (bits >= 0) {
            output.push_back(alphabet[(buffer >> bits) & 0x3F]);
            bits -= 6;
        }
    }
    if (bits > -6) output.push_back(alphabet[((buffer << 8) >> (bits + 8)) & 0x3F]);
    while (output.size() % 4) output.push_back('=');
    return output;
}

std::optional<std::string> base64_decode(std::string_view input) {
    if (input.size() % 4 != 0) return std::nullopt;

    std::string output;
    output.reserve((input.size() / 4) * 3);
    unsigned int buffer = 0;
    int bits = -8;
    bool padding_seen = false;
    int padding_count = 0;

    for (unsigned char byte : input) {
        if (std::isspace(byte)) return std::nullopt;
        if (byte == '=') {
            padding_seen = true;
            ++padding_count;
            if (padding_count > 2) return std::nullopt;
            continue;
        }
        if (padding_seen || decode_table[byte] < 0) return std::nullopt;

        buffer = (buffer << 6) | static_cast<unsigned int>(decode_table[byte]);
        bits += 6;
        if (bits >= 0) {
            output.push_back(static_cast<char>((buffer >> bits) & 0xFF));
            bits -= 8;
        }
    }

    if (padding_count == 1 && input.size() >= 4) {
        if (input[input.size() - 2] == '=') return std::nullopt;
    }
    if (padding_count && input.size() < 4) return std::nullopt;
    return output;
}

} // namespace unc::crypt_api
