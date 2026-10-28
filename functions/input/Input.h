#pragma once
#include <functional>
#include <string>
namespace unc::input_api {
struct Point { int x=0,y=0; };
using KeyQuery = std::function<bool(int)>;
using MouseQuery = std::function<bool(int)>;
using CursorQuery = std::function<Point()>;
class Input {
public:
    Input(KeyQuery key_query, MouseQuery mouse_query, CursorQuery cursor_query);
    [[nodiscard]] bool key_down(int key_code) const;
    [[nodiscard]] bool mouse_down(int button) const;
    [[nodiscard]] Point cursor_position() const;
private:
    KeyQuery key_query_;
    MouseQuery mouse_query_;
    CursorQuery cursor_query_;
};
} // namespace unc::input_api
