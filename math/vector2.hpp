#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "pukan/common.hpp"
#include "pukan/math/mfunctions.hpp"
#include "json/jobject.hpp"

namespace pukan {

const int PixelsPerMeter = 30;

template<typename T>
class Vec2
{
public:
   T x;
   T y;

public:
   Vec2();
   Vec2(T x_, T y_);
   Vec2(const Vec2<T> & copy);
   template<typename T2>
   Vec2(const Vec2<T2> & copy);
   template<typename T2>
   Vec2(const sf::Vector2<T2> & sfvec);

   Vec2<T> getHalf() const;
   float getAngleTo(const Vec2<T> & pos) const;
   float getDistanceTo(const Vec2<T> & pos) const;
   Vec2<T> getRoundedTo(int to) const;
   Vec2<T> getNormalized(const Vec2<T> & minPos, const Vec2<T> & maxPos);
   Vec2<T> getRotated(float angle, const Vec2<T> & offset);

   Vec2<T> operator +(const Vec2<T> & other) const;
   Vec2<T> operator -(const Vec2<T> & other) const;
   Vec2<T> operator *(T value) const;
   Vec2<T> operator /(T value) const;
   Vec2<T> operator ()(const Vec2<T> & addVec) const;
   Vec2<T> operator ()(T addX, T addY) const;
   void operator +=(const Vec2<T> & other);
   void operator -=(const Vec2<T> & other);
   void operator *=(T value);
   void operator /=(T value);
   bool operator ==(const Vec2<T> & other) const;
   bool operator !=(const Vec2<T> & other) const;
   operator sf::Vector2<T>() const;
   template<typename T2>
   operator sf::Vector2<T2>() const;
   operator std::string() const;

   static Vec2<T> fromB2Vec(const b2Vec2 & v);
   static Vec2<T> fromB2Pos(const b2Vec2 & v);
   static Vec2<T> fromB2Size(const b2Vec2 & v);
   b2Vec2 toB2Vec() const;
   b2Vec2 toB2Pos() const;
   b2Vec2 toB2Size() const;

   static Vec2<T> fromJson(const json::Object & jobj);
   json::Object toJson() const;

   struct Hash
   {
      unsigned operator ()(const Vec2<T> & vec) const;
   };
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

template<typename T>
inline Vec2<T>::Vec2()
   : Vec2<T>(0, 0)
{
}

template<typename T>
inline Vec2<T>::Vec2(T x_, T y_)
   : x(x_), y(y_)
{
}

template<typename T>
inline Vec2<T>::Vec2(const Vec2<T> & copy)
   : Vec2<T>(copy.x, copy.y)
{
}

template<typename T>
template<typename T2>
inline Vec2<T>::Vec2(const Vec2<T2> & copy)
   : Vec2<T>(static_cast<T>(copy.x),
             static_cast<T>(copy.y))
{
}

template<typename T>
template<typename T2>
inline Vec2<T>::Vec2(const sf::Vector2<T2> & sfvec)
   : Vec2<T>(static_cast<T>(sfvec.x),
             static_cast<T>(sfvec.y))
{
}

template<typename T>
inline Vec2<T> Vec2<T>::getHalf() const
{
   return Vec2<T>(x / 2.f, y / 2.f);
}

template<typename T>
inline float Vec2<T>::getAngleTo(const Vec2<T> & pos) const
{
   return std::atan2(pos.y - y, pos.x - x);
}

template<typename T>
inline float Vec2<T>::getDistanceTo(const Vec2<T> & pos) const
{
   return std::sqrt(std::pow(pos.x - x, 2) +
                    std::pow(pos.y - y, 2));
}

template<typename T>
inline Vec2<T> Vec2<T>::getRoundedTo(int to) const
{
   return Vec2<T>(pukan::roundTo(x, to),
                  pukan::roundTo(y, to));
}

template<typename T>
inline Vec2<T> Vec2<T>::getNormalized(const Vec2<T> & minPos, const Vec2<T> & maxPos)
{
   return Vec2<T>(pukan::normalize(x, minPos.x, maxPos.x),
                  pukan::normalize(y, minPos.y, maxPos.y));
}

template<typename T>
inline Vec2<T> Vec2<T>::getRotated(float angle, const Vec2<T> & offset)
{
   Vec2 originalPos = *this - offset;

   angle = pukan::degreesToRadians(angle);

   return Vec2(originalPos.x * std::cos(angle) - originalPos.y * std::sin(angle),
               originalPos.x * std::sin(angle) + originalPos.y * std::cos(angle))
         + offset;
}

template<typename T>
inline Vec2<T> Vec2<T>::operator +(const Vec2<T> & other) const
{
   return Vec2<T>(x + other.x, y + other.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator -(const Vec2<T> & other) const
{
   return Vec2<T>(x - other.x, y - other.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator *(T value) const
{
   return Vec2<T>(x * value, y * value);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator /(T value) const
{
   return Vec2<T>(x / value, y / value);
}

template<typename T>
inline Vec2<T> Vec2<T>::operator ()(const Vec2<T> & addVec) const
{
   return *this + addVec;
}


template<typename T>
inline Vec2<T> Vec2<T>::operator ()(T addX, T addY) const
{
   return Vec2<T>(x + addX, y + addY);
}

template<typename T>
inline void Vec2<T>::operator +=(const Vec2<T> & other)
{
   x += other.x;
   y += other.y;
}

template<typename T>
inline void Vec2<T>::operator -=(const Vec2<T> & other)
{
   x -= other.x;
   y -= other.y;
}

template<typename T>
inline void Vec2<T>::operator *=(T value)
{
   x *= value;
   y *= value;
}


template<typename T>
inline void Vec2<T>::operator /=(T value)
{
   x /= value;
   y /= value;
}

template<typename T>
inline bool Vec2<T>::operator ==(const Vec2<T> & other) const
{
   return x == other.x && y == other.y;
}

template<typename T>
inline bool Vec2<T>::operator !=(const Vec2<T> & other) const
{
   return !(*this == other);
}

template<typename T>
inline Vec2<T>::operator sf::Vector2<T>() const
{
   return sf::Vector2<T>(x, y);
}

template<typename T>
template<typename T2>
inline Vec2<T>::operator sf::Vector2<T2>() const
{
   return sf::Vector2<T2>(static_cast<T2>(x),
                          static_cast<T2>(y));
}

template<typename T>
Vec2<T>::operator std::string() const
{
   return (b::format("Vec2(x: %1%, y: %2%)") % x % y).str();
}

template<typename T>
inline Vec2<T> Vec2<T>::fromB2Vec(const b2Vec2 & v)
{
   return Vec2<T>(v.x, v.y);
}

template<typename T>
inline Vec2<T> Vec2<T>::fromB2Pos(const b2Vec2 & v)
{
   return Vec2<T>(v.x * PixelsPerMeter, -v.y * PixelsPerMeter);
}

template<typename T>
inline Vec2<T> Vec2<T>::fromB2Size(const b2Vec2 & v)
{
   return Vec2<T>(v.x * PixelsPerMeter, v.y * PixelsPerMeter);
}

template<typename T>
inline b2Vec2 Vec2<T>::toB2Vec() const
{
   return b2Vec2(x, y);
}

template<typename T>
inline b2Vec2 Vec2<T>::toB2Pos() const
{
   return b2Vec2(x / PixelsPerMeter, -y / PixelsPerMeter);
}

template<typename T>
inline b2Vec2 Vec2<T>::toB2Size() const
{
   return b2Vec2(x / PixelsPerMeter,  y / PixelsPerMeter);
}

template<typename T>
inline Vec2<T> Vec2<T>::fromJson(const json::Object & jobj)
{
   return Vec2f(jobj.get<T>("x"),
                jobj.get<T>("y"));
}

template<typename T>
inline json::Object Vec2<T>::toJson() const
{
   json::Object jvec2(json::Object::Hash);
   jvec2.add("x", x);
   jvec2.add("y", y);
   return jvec2;
}

template<typename T>
inline unsigned Vec2<T>::Hash::operator ()(const Vec2<T> & vec) const
{
   return std::hash<T>()(vec.x) ^ std::hash<T>()(vec.y);
}

}

#endif // VECTOR2_HPP
