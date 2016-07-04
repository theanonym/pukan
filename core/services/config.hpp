#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "pukan/common.hpp"
#include "pukan/singleton.hpp"

namespace pukan {

struct Config : public Singleton<Config>
{
   int fpsLimit          = 60;
   int antialiasingLevel = 0;
   float blurLevel = 0.0;
   float physicsAccuracy = 1.f;

   sf::String windowTitle;
   int windowWidht;
   int windowHeight;

   bool customCursor = true;

   bool destructible = false;
   bool drawOutline  = false;
   bool drawAABB = false;
   bool drawSensors = false;
   bool pixelFix = false;
   float gameSpeed = 1.f;

   bfs::path workingDir;

   friend std::ostream & operator << (std::ostream &, const Config &);
};

}

#endif // CONFIG_HPP
