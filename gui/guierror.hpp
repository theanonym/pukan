#ifndef GUIERROR_HPP
#define GUIERROR_HPP

#include "pukan/common.hpp"

namespace pukan {
namespace gui {

class Error : public std::exception
{
public:
   Error(const std::string & what);

   const char * what() const noexcept(true);

private:
   std::string _what;
};

} // ns gui
} // ns pukan

#endif // GUIERROR_HPP
