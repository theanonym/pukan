#ifndef MFUNCTIONS_HPP
#define MFUNCTIONS_HPP

#include "pukan/common.hpp"

namespace pukan {

static inline float radiansToDegrees(float radians)
{
   return radians * 57.2957795;
}

static inline float degreesToRadians(float degrees)
{
   return degrees * 0.01745329;
}

static inline int roundTo(float from_, int to)
{
   int from = std::floor(from_);
   int mod = from % to;

   if(mod < 3)
      return from - mod;
   else
      return from - mod + to;
}

template<typename T>
static inline float normalize(T value, T min, T max)
{
   return (value - min) / (max - min);
}

}

#endif // MFUNCTIONS_HPP
