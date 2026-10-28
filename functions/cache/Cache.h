#pragma once
#include <optional>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>
namespace unc::cache_api {
class Cache {
public:
    [[nodiscard]] bool has(const std::string& key) const;
    [[nodiscard]] std::optional<std::string> get(const std::string& key) const;
    void set(std::string key, std::string value);
    [[nodiscard]] bool erase(const std::string& key);
    void clear();
    [[nodiscard]] std::vector<std::string> keys() const;
    [[nodiscard]] std::size_t size() const;
private:
    mutable std::shared_mutex mutex_;
    std::unordered_map<std::string, std::string> values_;
};
} // namespace unc::cache_api
