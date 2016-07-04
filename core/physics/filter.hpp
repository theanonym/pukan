#ifndef FILTER_HPP
#define FILTER_HPP

#include "pukan/common.hpp"

namespace json { class Object; }

namespace pukan {

class Filter
{
public:
   enum Bits
   {
      None = 0,
      A = 0x0001,
      B = 0x0002,
      C = 0x0004,
      D = 0x0008,
      E = 0x0010,
      F = 0x0016,
      G = 0x0032
   };

public:
   Filter();
   Filter(sf::Uint16 categoryBits, sf::Uint16 maskBits);

   sf::Uint16 getCategoryBits() const;
   sf::Uint16 getMaskBits() const;

   static Filter fromB2Filter(const b2Filter & b2filter);
   b2Filter toB2Filter() const;

   static Filter fromJson(const json::Object & js);
   json::Object toJson() const;

private:
   sf::Uint16 _categoryBits;
   sf::Uint16 _maskBits;
};

}

#endif // FILTER_HPP
