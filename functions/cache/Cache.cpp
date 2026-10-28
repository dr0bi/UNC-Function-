#include "Cache.h"
#include <mutex>
#include <algorithm>
namespace unc::cache_api {
bool Cache::has(const std::string& key) const { std::shared_lock lock(mutex_); return values_.find(key) != values_.end(); }
std::optional<std::string> Cache::get(const std::string& key) const { std::shared_lock lock(mutex_); auto it=values_.find(key); if(it==values_.end()) return std::nullopt; return it->second; }
void Cache::set(std::string key, std::string value) { std::unique_lock lock(mutex_); values_.insert_or_assign(std::move(key),std::move(value)); }
bool Cache::erase(const std::string& key) { std::unique_lock lock(mutex_); return values_.erase(key)>0; }
void Cache::clear() { std::unique_lock lock(mutex_); values_.clear(); }
std::vector<std::string> Cache::keys() const { std::shared_lock lock(mutex_); std::vector<std::string> out; out.reserve(values_.size()); for(const auto& item:values_) out.push_back(item.first); std::sort(out.begin(),out.end()); return out; }
std::size_t Cache::size() const { std::shared_lock lock(mutex_); return values_.size(); }
} // namespace unc::cache_api
