#include "Console.h"

#include <utility>

namespace unc::console_api {

Console::Console(Sink sink) : sink_(std::move(sink)) {}

void Console::emit(Level level, std::string_view message) const {
    if (!sink_) return;
    std::lock_guard<std::mutex> lock(mutex_);
    sink_(level, message);
}

void Console::print(std::string_view message) const { emit(Level::Info, message); }
void Console::info(std::string_view message) const { emit(Level::Info, message); }
void Console::warn(std::string_view message) const { emit(Level::Warning, message); }
void Console::error(std::string_view message) const { emit(Level::Error, message); }
void Console::debug(std::string_view message) const { emit(Level::Debug, message); }

} // namespace unc::console_api
