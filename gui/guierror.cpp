#include "pukan/gui/guierror.hpp"

namespace pukan {
namespace gui {

Error::Error(const std::string & what)
   : _what("GUI: " + what)
{
}

const char * Error::what() const noexcept(true)
{
   return _what.c_str();
}

} // ns gui
} // ns pukan
