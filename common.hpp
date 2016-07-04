#ifndef COMMON_HPP
#define COMMON_HPP

// STL
//--------------------------
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <initializer_list>
#include <list>
#include <limits>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
#include <exception>
#include <queue>
//--------------------------


// SFML
//--------------------------
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
//--------------------------


// Box2D
//--------------------------
#include <Box2D/Box2D.h>
//--------------------------


// Booost
//--------------------------
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/current_function.hpp>

namespace b   = boost;
namespace bfs = boost::filesystem;

//--------------------------

#define ythrow(exc, msg) \
   do {  \
   std::stringstream exc_str; \
   exc_str << msg << "\n" \
   << __FILE__ << ":" << __LINE__ \
   << ": " << BOOST_CURRENT_FUNCTION ;  \
   throw exc(exc_str.str()); \
   } while(0)

#define YOBA_UNUSED(x) (void)(x)

#define P(x) std::cerr << __FILE__ << ":" << __LINE__ << ": " << x << '\n'

#endif // COMMON_HPP
