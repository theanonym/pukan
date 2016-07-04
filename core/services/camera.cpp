#include "pukan/core/services/camera.hpp"

namespace pukan {

Camera::Camera()
{
}

Camera::Camera(const Vec2f & center, const Vec2f & size)
   : sf::View(center, size)
{
}

Camera::Camera(const Rectf & rect)
   : sf::View(rect)
{
}

Rectf Camera::getRect() const
{
   return Rectf(sf::View::getCenter() - sf::View::getSize() / 2.f,
                sf::View::getSize());
}

void Camera::setRect(const Rectf & rect)
{
   sf::View::setCenter(rect.getCenter());
}

}
