#ifndef TEMPORARY_HPP
#define TEMPORARY_HPP

#include "pukan/common.hpp"

namespace pukan {

class Temporary
{
public:
   void removeAfter(float seconds);
   float getElaspedTime() const;
   bool hasTimeLimit() const;
   bool needToRemove() const;

private:
   sf::Clock _timer;
   float _timelimit = -1;
};

}

#endif // TEMPORARY_HPP
