#include "pukan/core/physics/bodyiterator.hpp"
#include "pukan/core/physics/body.hpp"

namespace pukan {

BodyIterator::BodyIterator(const b2Body * node, int bodyCount)
   : _node(node),
     _bodyCount(bodyCount)
{
}

BodyIterator::BodyIterator(const BodyIterator & copy)
   : _node(copy._node),
     _bodyCount(copy._bodyCount)
{
}

Body * BodyIterator::get() const
{
   assert(*this);
   return static_cast<Body *>(_node->GetUserData());
}

bool BodyIterator::hasNext() const
{
   return _node->GetNext() != 0;
}

int BodyIterator::getCount() const
{
   return _bodyCount;
}

BodyIterator::operator bool() const
{
   return _node != 0;
}

BodyIterator & BodyIterator::operator++()
{
   _node = _node->GetNext();
   return *this;
}

BodyIterator BodyIterator::operator++(int)
{
   BodyIterator old(*this);
   operator++();
   return old;
}

}
