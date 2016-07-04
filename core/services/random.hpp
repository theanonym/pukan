#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "pukan/common.hpp"
#include "pukan/singleton.hpp"

namespace pukan {

class Random : public Singleton<Random>
{
public:
   template<typename T = int>
   T getInt(T min, T max)
   {
      return std::uniform_int_distribution<T>(min, max)(_rd);
   }

   template<typename T = float>
   T getReal(T min, T max)
   {
      return std::uniform_real_distribution<T>(min, max)(_rd);
   }

   bool getBool()
   {
      return static_cast<bool>(std::uniform_int_distribution<int>(0, 1)(_rd));
   }

private:
   std::random_device _rd;
};

}

#endif // RANDOM_HPP
