#ifndef RECT_HPP
#define RECT_HPP

#include "pukan/common.hpp"
#include "pukan/math/vector2.hpp"

namespace pukan {

//  TODO Combine
template<typename T>
class Rect
{
public:
   T x;
   T y;
   T w;
   T h;

public:
   Rect();
   Rect(T x_, T y_, T w_, T h_);
   Rect(const Vec2<T> & pos, const Vec2<T> & size);
   Rect(const Rect<T> & copy);
   template<typename T2>
   Rect(const Rect<T2> & copy);
   template<typename T2>
   Rect(const sf::Rect<T2> & sfrect);

   Vec2<T> getPos() const;
   Vec2<T> getSize() const;
   Vec2<T> getCenter() const;
   Vec2<T> getTopLeft() const;
   Vec2<T> getTopRight() const;
   Vec2<T> getBottomLeft() const;
   Vec2<T> getBottomRight() const;
   Vec2<T> getMiddleLeft() const;
   Vec2<T> getMiddleRight() const;
   Vec2<T> getMiddleTop() const;
   Vec2<T> getMiddleBottom() const;

   bool contains(const Vec2<T> & p) const;

   bool operator ==(const Rect<T> & other) const;
   bool operator !=(const Rect<T> & other) const;
   operator sf::Rect<T>() const;
   operator std::string() const;

   static Rect<T> fromB2AABB(const b2AABB & b2aabb);
   b2AABB toB2AABB() const;

   static Rect<T> fromJson(const json::Object & jobj);
   json::Object toJson() const
   {
      json::Object jrect(json::Object::Hash);
      jrect.add("x", x);
      jrect.add("y", y);
      jrect.add("w", w);
      jrect.add("h", h);
      return jrect;
   }

   struct Hash
   {
      unsigned operator ()(const Rect<T> & rect) const;
   };
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;

template<typename T>
inline Rect<T>::Rect()
   : Rect<T>(0, 0, 0, 0)
{
}

template<typename T>
inline Rect<T>::Rect(T x_, T y_, T w_, T h_)
   : x(x_), y(y_), w(w_), h(h_)
{
}

template<typename T>
inline Rect<T>::Rect(const Vec2<T> & pos, const Vec2<T> & size)
   : Rect<T>(pos.x, pos.y, size.x, size.y)
{
}

template<typename T>
inline Rect<T>::Rect(const Rect<T> & copy)
   : x(copy.x), y(copy.y), w(copy.w), h(copy.h)
{
}

template<typename T>
template<typename T2>
inline Rect<T>::Rect(const Rect<T2> & copy)
   : x(static_cast<T>(copy.x)), y(static_cast<T>(copy.y)),
     w(static_cast<T>(copy.w)), h(static_cast<T>(copy.h))
{
}

template<typename T>
template<typename T2>
inline Rect<T>::Rect(const sf::Rect<T2> & sfrect)
   : Rect<T>(static_cast<T>(sfrect.left),  static_cast<T>(sfrect.top),
             static_cast<T>(sfrect.width), static_cast<T>(sfrect.height))
{
}

template<typename T>
inline Vec2<T> Rect<T>::getPos() const
{
   return Vec2<T>(x, y);
}

template<typename T>
inline Vec2<T> Rect<T>::getSize() const
{
   return Vec2<T>(w, h);
}

template<typename T>
inline Vec2<T> Rect<T>::getCenter() const
{
   return Vec2<T>(x + w / 2.f,
                  y + h / 2.f);
}

template<typename T>
inline Vec2<T> Rect<T>::getTopLeft() const
{
   return Vec2<T>(x, y);
}

template<typename T>
inline Vec2<T> Rect<T>::getTopRight() const
{
   return Vec2<T>(x + w, y);
}

template<typename T>
inline Vec2<T> Rect<T>::getBottomLeft() const
{
   return Vec2<T>(x, y + h);
}

template<typename T>
inline Vec2<T> Rect<T>::getBottomRight() const
{
   return Vec2<T>(x + w, y + h);
}

template<typename T>
inline Vec2<T> Rect<T>::getMiddleLeft() const
{
   return Vec2<T>(x, y + h / 2.f);
}

template<typename T>
inline Vec2<T> Rect<T>::getMiddleRight() const
{
   return Vec2<T>(x + w, y + h / 2.f);
}

template<typename T>
inline Vec2<T> Rect<T>::getMiddleTop() const
{
   return Vec2<T>(x + w / 2.f, y);
}

template<typename T>
inline Vec2<T> Rect<T>::getMiddleBottom() const
{
   return Vec2<T>(x + w / 2.f, y + h);
}

template<typename T>
inline bool Rect<T>::contains(const Vec2<T> & p) const
{
   return sf::Rect<T>(x, y, w, h).contains(p);
}

template<typename T>
inline bool Rect<T>::operator ==(const Rect<T> & other) const
{
   return x == other.x && y == other.y
       && w == other.w && h == other.h;
}

template<typename T>
inline bool Rect<T>::operator !=(const Rect<T> & other) const
{
   return !(*this == other);
}

template<typename T>
Rect<T>::operator sf::Rect<T>() const
{
   return sf::Rect<T>(x, y, w, h);
}

template<typename T>
Rect<T>::operator std::string() const
{
   return (b::format("Rect(x: %1%, y: %2%, w: %3%, h: %4%)") % x % y % w % h).str();
}

template<typename T>
inline Rect<T> Rect<T>::fromB2AABB(const b2AABB & b2aabb)
{
   Vec2<T> lower = Vec2<T>::fromB2Pos(b2aabb.lowerBound); // Левый нижний
   Vec2<T> upper = Vec2<T>::fromB2Pos(b2aabb.upperBound); // Правый верхний

   return Rect<T>(lower.x, upper.y, upper.x - lower.x, lower.y - upper.y);
}

template<typename T>
inline b2AABB Rect<T>::toB2AABB() const
{
   return b2AABB();
}

template<typename T>
inline Rect<T> Rect<T>::fromJson(const json::Object & jobj)
{
   return Rect(jobj.get<T>("x"),
               jobj.get<T>("y"),
               jobj.get<T>("w"),
               jobj.get<T>("h"));
}

//template<typename T>
//inline json::Object Rect<T>::toJson() const
//{
//   json::Object jrect(json::Object::Hash);
//   jrect.add("x", x);
//   jrect.add("y", y);
//   jrect.add("w", w);
//   jrect.add("h", h);
//   return jrect;
//}

template<typename T>
inline unsigned Rect<T>::Hash::operator ()(const Rect<T> & rect) const
{
   return std::hash<T>()(rect.x) ^ std::hash<T>()(rect.y) ^
          std::hash<T>()(rect.w) ^ std::hash<T>()(rect.h);
}

}

#endif // RECT_HPP
