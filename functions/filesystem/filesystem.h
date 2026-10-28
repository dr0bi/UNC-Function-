#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace unc::filesystem_api {

// All operations are confined to the configured workspace root.
// Paths that escape the root are rejected.
class Filesystem {
public:
    explicit Filesystem(std::filesystem::path workspace_root);

    [[nodiscard]] std::optional<std::string> read_file(const std::string& path) const;
    [[nodiscard]] bool write_file(const std::string& path, const std::string& contents) const;
    [[nodiscard]] bool append_file(const std::string& path, const std::string& contents) const;
    [[nodiscard]] bool delete_file(const std::string& path) const;
    [[nodiscard]] bool make_directory(const std::string& path) const;
    [[nodiscard]] bool is_file(const std::string& path) const;
    [[nodiscard]] bool is_directory(const std::string& path) const;
    [[nodiscard]] std::vector<std::string> list_files(const std::string& path) const;

private:
    std::filesystem::path root_;
    [[nodiscard]] std::optional<std::filesystem::path> resolve(const std::string& path) const;
};

} // namespace unc::filesystem_api
