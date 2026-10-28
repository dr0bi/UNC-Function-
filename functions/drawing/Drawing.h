#pragma once
#include <cstdint>
#include <memory>
#include <string>
namespace unc::drawing_api {
struct Color { std::uint8_t r=255,g=255,b=255,a=255; };
struct Vec2 { float x=0.0f,y=0.0f; };
class Canvas {
public:
    virtual ~Canvas() = default;
    virtual void line(Vec2 from, Vec2 to, Color color, float thickness) = 0;
    virtual void rectangle(Vec2 position, Vec2 size, Color color, float thickness, bool filled) = 0;
    virtual void circle(Vec2 center, float radius, Color color, float thickness, bool filled) = 0;
    virtual void text(Vec2 position, const std::string& value, Color color, float size) = 0;
};
// Rendering is supplied by the local host; this module does not access a game renderer.
class Drawing {
public:
    explicit Drawing(std::shared_ptr<Canvas> canvas);
    [[nodiscard]] bool available() const noexcept;
    [[nodiscard]] bool line(Vec2 from, Vec2 to, Color color, float thickness = 1.0f) const;
    [[nodiscard]] bool rectangle(Vec2 position, Vec2 size, Color color, float thickness = 1.0f, bool filled = false) const;
    [[nodiscard]] bool circle(Vec2 center, float radius, Color color, float thickness = 1.0f, bool filled = false) const;
    [[nodiscard]] bool text(Vec2 position, const std::string& value, Color color, float size = 14.0f) const;
private:
    std::shared_ptr<Canvas> canvas_;
};
} // namespace unc::drawing_api
