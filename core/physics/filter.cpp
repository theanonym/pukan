#include "pukan/core/physics/filter.hpp"
#include "json/jobject.hpp"

namespace pukan {

Filter::Filter()
   : Filter(None, None)
{
}

Filter::Filter(sf::Uint16 categoryBits, sf::Uint16 maskBits)
   : _categoryBits(categoryBits),
     _maskBits(maskBits)
{
}

sf::Uint16 Filter::getCategoryBits() const
{
   return _categoryBits;
}

sf::Uint16 Filter::getMaskBits() const
{
   return _maskBits;
}

Filter Filter::fromB2Filter(const b2Filter & b2filter)
{
   return Filter(b2filter.categoryBits, b2filter.maskBits);
}

b2Filter Filter::toB2Filter() const
{
   b2Filter b2filter;
   b2filter.categoryBits = getCategoryBits();
   b2filter.maskBits = getMaskBits();

   return b2filter;
}

Filter Filter::fromJson(const json::Object & js)
{
   return Filter(js.get<sf::Uint16>("categoryBits"),
                 js.get<sf::Uint16>("maskBits"));
}

json::Object Filter::toJson() const
{
   json::Object js(json::Object::Hash);
   js.add("categoryBits", getCategoryBits())
     .add("maskBits", getMaskBits());
   return js;
}

}
