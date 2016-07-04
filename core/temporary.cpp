#include "pukan/core/temporary.hpp"

namespace pukan {

void Temporary::removeAfter(float seconds)
{
   if(hasTimeLimit())
      return;

   _timer.restart();
   _timelimit = seconds;
}

float Temporary::getElaspedTime() const
{
   return _timer.getElapsedTime().asSeconds();
}

bool Temporary::hasTimeLimit() const
{
   return _timelimit >= 0;
}

bool Temporary::needToRemove() const
{
   if(_timelimit < 0)
      return false;

   return getElaspedTime() > _timelimit;
}

}
