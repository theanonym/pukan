#ifndef BASEAPPLICATION_HPP
#define BASEAPPLICATION_HPP

#include "pukan/common.hpp"

namespace pukan {

class BaseApplication
{
public:
   BaseApplication(int argc, char ** argv);

   void run();

protected:
   virtual void init() = 0;
   virtual void clean() = 0;

   virtual void input(const sf::Event & event) = 0;
   virtual void update() = 0;
   virtual void render() = 0;
};

}

#endif // BASEAPPLICATION_HPP
