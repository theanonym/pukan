#ifndef WORLDQUERRY_HPP
#define WORLDQUERRY_HPP

#include "pukan/common.hpp"

namespace pukan {

class Body;

class WorldQuerry : public b2QueryCallback
{
public:
   WorldQuerry();
   WorldQuerry(WorldQuerry && move);

   bool ReportFixture(b2Fixture * fixture);

   std::vector<Body *> & getList();
   Body * getFirst() const;
   bool isEmpty() const;

private:
   std::vector<Body *> _found;
};

}

#endif // WORLDQUERRY_HPP
