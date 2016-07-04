#include "pukan/core/baseapplication.hpp"
#include "pukan/core/services/renderer.hpp"
#include "pukan/core/services/config.hpp"
#include "pukan/core/services/logger.hpp"

namespace pukan {

BaseApplication::BaseApplication(int argc, char ** argv)
{
   YOBA_UNUSED(argc);

   bfs::path workingDir(argv[0]);
   workingDir.remove_filename();
   Config::get().workingDir = workingDir;
}

void BaseApplication::run()
{
   init();

   sf::Clock flushTimer;

   while(Renderer::get().getWindow().isOpen())
   {
      try
      {
         sf::Event event;
         while(Renderer::get().getWindow().pollEvent(event))
            input(event);
         update();
         render();
      }
      catch(std::exception & e)
      {
         Logger::get().error() << e.what();
      }

      if(flushTimer.getElapsedTime().asSeconds() >= 1.f)
      {
         std::cout << std::flush;
         flushTimer.restart();
      }
   }

   clean();
}

}
