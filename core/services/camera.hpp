#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"

namespace pukan {

class Camera : public sf::View
{
public:
   Camera();
   Camera(const Vec2f & center, const Vec2f & size);
   Camera(const Rectf & rect);

   Rectf getRect() const;
   void setRect(const Rectf & rect);
};

}

#endif // CAMERA_HPP
