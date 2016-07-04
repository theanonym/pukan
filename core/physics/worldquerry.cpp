#include "pukan/core/physics/worldquerry.hpp"

namespace pukan {

WorldQuerry::WorldQuerry()
{
}

WorldQuerry::WorldQuerry(WorldQuerry && move)
   : _found(std::move(move._found))
{
}

bool WorldQuerry::ReportFixture(b2Fixture * fixture)
{
   _found.push_back(static_cast<Body *>(fixture->GetBody()->GetUserData()));
   return true;
}

std::vector<Body *> & WorldQuerry::getList()
{
   return _found;
}

Body * WorldQuerry::getFirst() const
{
   return _found[0];
}

bool WorldQuerry::isEmpty() const
{
   return _found.empty();
}

}
