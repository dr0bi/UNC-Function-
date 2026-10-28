#include "Input.h"
#include <utility>
namespace unc::input_api {
Input::Input(KeyQuery k,MouseQuery m,CursorQuery c):key_query_(std::move(k)),mouse_query_(std::move(m)),cursor_query_(std::move(c)){}
bool Input::key_down(int code) const { return key_query_ && key_query_(code); }
bool Input::mouse_down(int button) const { return mouse_query_ && mouse_query_(button); }
Point Input::cursor_position() const { return cursor_query_ ? cursor_query_() : Point{}; }
} // namespace unc::input_api
