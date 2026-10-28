#include "Cache.h"
#include "Crypt.h"
#include "Misc.h"
#include <cassert>
#include <iostream>

int main() {
    using namespace unc;
    cache_api::Cache cache;
    assert(!cache.has("missing"));
    cache.set("key", "value");
    assert(cache.has("key"));
    assert(cache.get("key").value() == "value");
    assert(cache.size() == 1);
    assert(cache.erase("key"));
    assert(!cache.get("key").has_value());

    assert(misc_api::trim("  hello \t") == "hello");
    const auto parts = misc_api::split("a,,b", ',', true);
    assert(parts.size() == 3 && parts[1].empty());
    assert(misc_api::starts_with("foobar", "foo"));
    assert(misc_api::ends_with("foobar", "bar"));
    assert(misc_api::replace_all("one fish", "fish", "bird") == "one bird");

    const std::string input = "UNC test string";
    const auto encoded = crypt_api::base64_encode(input);
    const auto decoded = crypt_api::base64_decode(encoded);
    assert(decoded.has_value() && *decoded == input);
    assert(!crypt_api::base64_decode("not base64!").has_value());

    std::cout << "all tests passed\n";
    return 0;
}
