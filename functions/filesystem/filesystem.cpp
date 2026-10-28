#include "filesystem.h"

#include <fstream>
#include <system_error>

namespace unc::filesystem_api {
namespace fs = std::filesystem;

Filesystem::Filesystem(fs::path workspace_root) {
    std::error_code ec;
    fs::create_directories(workspace_root, ec);
    root_ = fs::weakly_canonical(fs::absolute(workspace_root), ec);
    if (ec) {
        root_ = fs::absolute(std::move(workspace_root)).lexically_normal();
    }
}

std::optional<fs::path> Filesystem::resolve(const std::string& path) const {
    const fs::path requested(path);
    if (requested.is_absolute()) return std::nullopt;

    std::error_code ec;
    const fs::path candidate = fs::weakly_canonical((root_ / requested).lexically_normal(), ec);
    if (ec) return std::nullopt;

    auto root_it = root_.begin();
    auto candidate_it = candidate.begin();
    for (; root_it != root_.end(); ++root_it, ++candidate_it) {
        if (candidate_it == candidate.end() || *root_it != *candidate_it) {
            return std::nullopt;
        }
    }
    return candidate;
}

std::optional<std::string> Filesystem::read_file(const std::string& path) const {
    const auto resolved = resolve(path);
    if (!resolved) return std::nullopt;

    std::ifstream input(*resolved, std::ios::binary);
    if (!input) return std::nullopt;
    return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

bool Filesystem::write_file(const std::string& path, const std::string& contents) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;

    std::error_code ec;
    fs::create_directories(resolved->parent_path(), ec);
    if (ec) return false;

    std::ofstream output(*resolved, std::ios::binary | std::ios::trunc);
    if (!output) return false;
    output.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    return output.good();
}

bool Filesystem::append_file(const std::string& path, const std::string& contents) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;

    std::error_code ec;
    fs::create_directories(resolved->parent_path(), ec);
    if (ec) return false;

    std::ofstream output(*resolved, std::ios::binary | std::ios::app);
    if (!output) return false;
    output.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    return output.good();
}

bool Filesystem::delete_file(const std::string& path) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;
    std::error_code ec;
    return fs::remove(*resolved, ec) && !ec;
}

bool Filesystem::make_directory(const std::string& path) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;
    std::error_code ec;
    return fs::create_directories(*resolved, ec) || (!ec && fs::is_directory(*resolved, ec));
}

bool Filesystem::is_file(const std::string& path) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;
    std::error_code ec;
    return fs::is_regular_file(*resolved, ec) && !ec;
}

bool Filesystem::is_directory(const std::string& path) const {
    const auto resolved = resolve(path);
    if (!resolved) return false;
    std::error_code ec;
    return fs::is_directory(*resolved, ec) && !ec;
}

std::vector<std::string> Filesystem::list_files(const std::string& path) const {
    std::vector<std::string> result;
    const auto resolved = resolve(path);
    if (!resolved) return result;

    std::error_code ec;
    fs::directory_iterator it(*resolved, ec), end;
    if (ec) return result;
    for (; it != end; it.increment(ec)) {
        if (ec) break;
        result.push_back(it->path().filename().string());
    }
    return result;
}

} // namespace unc::filesystem_api
