#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "pukan/common.hpp"
#include "pukan/singleton.hpp"

namespace pukan {

class Logger : public Singleton<Logger>
{
   class TmpLogger;

public:
   TmpLogger info(const std::string & format);
   TmpLogger debug(const std::string & format);
   TmpLogger error(const std::string & format);
   TmpLogger info();
   TmpLogger debug();
   TmpLogger error();

private:
   class TmpLogger
   {
   public:
      TmpLogger(std::ostream & out, std::string format);
      ~TmpLogger();

      template<typename T>
      TmpLogger & operator << (const T & x)
      {
         _format.bind_arg(_format.cur_arg(), x);
         return *this;
      }

      template<typename T>
      TmpLogger & operator % (const T & x)
      {
         _format.bind_arg(_format.cur_arg(), x);
         return *this;
      }

   private:
      std::ostream & _out;
      b::format  _format;
   };
};

}

#endif // LOGGER_HPP
