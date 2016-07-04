#ifndef JOINTITERATOR_HPP
#define JOINTITERATOR_HPP

#include "pukan/common.hpp"

namespace pukan {

class Joint;

class JointIterator
{
public:
   JointIterator(const b2Body * node);
   JointIterator(const JointIterator & copy);

   Joint * get();
   const Joint * get() const;
   bool hasNext() const;

   operator bool() const;
   JointIterator & operator++();
   JointIterator operator++(int);

private:
   const b2Body * _node = nullptr;
};

}

#endif // JOINTITERATOR_HPP
