#ifndef BODYITERATOR_HPP
#define BODYITERATOR_HPP

#include "pukan/common.hpp"

namespace pukan {

class Body;

class BodyIterator
{
public:
   BodyIterator(const b2Body * node, int bodyCount);
   BodyIterator(const BodyIterator & copy);

   Body * get() const;
   bool hasNext() const;
   int getCount() const;

   operator bool() const;
   BodyIterator & operator++();
   BodyIterator   operator++(int);

private:
   const b2Body * _node = nullptr;
   int _bodyCount = -1;
};

}

#endif // BODYITERATOR_HPP
