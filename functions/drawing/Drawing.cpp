#include "Drawing.h"
#include <cmath>
#include <utility>
namespace unc::drawing_api {
Drawing::Drawing(std::shared_ptr<Canvas> canvas):canvas_(std::move(canvas)){}
bool Drawing::available() const noexcept { return static_cast<bool>(canvas_); }
bool Drawing::line(Vec2 a,Vec2 b,Color c,float t) const { if(!canvas_ || !std::isfinite(t) || t<=0) return false; canvas_->line(a,b,c,t); return true; }
bool Drawing::rectangle(Vec2 p,Vec2 s,Color c,float t,bool f) const { if(!canvas_ || !std::isfinite(t) || t<=0 || !std::isfinite(s.x) || !std::isfinite(s.y) || s.x<0 || s.y<0) return false; canvas_->rectangle(p,s,c,t,f); return true; }
bool Drawing::circle(Vec2 p,float r,Color c,float t,bool f) const { if(!canvas_ || !std::isfinite(r) || r<0 || !std::isfinite(t) || t<=0) return false; canvas_->circle(p,r,c,t,f); return true; }
bool Drawing::text(Vec2 p,const std::string& v,Color c,float s) const { if(!canvas_ || !std::isfinite(s) || s<=0) return false; canvas_->text(p,v,c,s); return true; }
} // namespace unc::drawing_api
