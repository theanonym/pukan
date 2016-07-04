#include "pukan/core/services/logger.hpp"

namespace pukan {

Logger::TmpLogger Logger::info(const std::string & format)
{
   return TmpLogger(std::cout, "[Info]: " + format);
}

Logger::TmpLogger Logger::debug(const std::string & format)
{
   return TmpLogger(std::cout, "[Debug]: " + format);
}

Logger::TmpLogger Logger::error(const std::string & format)
{
   return TmpLogger(std::cerr, "[Error]: " + format);
}

Logger::TmpLogger Logger::info()
{
   return info("%1%");
}

Logger::TmpLogger Logger::debug()
{
   return debug("%1%");
}

Logger::TmpLogger Logger::error()
{
   return error("%1%");
}

Logger::TmpLogger::TmpLogger(std::ostream & out, std::string format)
   : _out(out),
     _format(format)
{
}

Logger::TmpLogger::~TmpLogger()
{
   _out << _format.str() << '\n';
}

}
