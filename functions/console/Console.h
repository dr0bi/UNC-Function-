#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <string_view>

namespace unc::console_api {

enum class Level { Info, Warning, Error, Debug };
using Sink = std::function<void(Level, std::string_view)>;

// A host-provided sink keeps this module independent of any UI or terminal.
class Console {
public:
    explicit Console(Sink sink);

    void print(std::string_view message) const;
    void info(std::string_view message) const;
    void warn(std::string_view message) const;
    void error(std::string_view message) const;
    void debug(std::string_view message) const;

private:
    Sink sink_;
    mutable std::mutex mutex_;
    void emit(Level level, std::string_view message) const;
};

} // namespace unc::console_api
