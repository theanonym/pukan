#include "pukan/core/services/renderer.hpp"
#include "pukan/core/services/config.hpp"

namespace pukan {

Renderer::Renderer()
{
//   _renderTexture = new sf::RenderTexture;
//   _renderTexture->create(1250, 610);
}

void Renderer::fill(const sf::Color & color)
{
      _window.clear(color);

//   if(isRenderToTexture())
//   {
//      _renderTexture->clear(color);

//   }


}

void Renderer::render()
{
   /*
   if(isRenderToTexture())
   {
      throw;

      _window.draw(sf::RectangleShape());
      _renderTexture->draw(sf::RectangleShape());
      _renderTexture->display();

//      sf::Texture tmp(_renderTexture->getTexture());
      sf::Sprite renderSprite(_renderTexture->getTexture());
//      if(Vec2f(getCamera().getCenter() - getCamera().getSize() / 2.f) != Vec2f())
//         renderSprite.setPosition(getCamera().getCenter() - getCamera().getSize() / 2.f);
//      renderSprite.setPosition(0,0);
      getWindow().draw(renderSprite);

      setRenderToTexture(false);
   }
   */

   _window.display();
}

void Renderer::close()
{
   getWindow().close();
}

void Renderer::draw(const sf::Drawable & drawable)
{
//   if(isRenderToTexture())
//      _renderTexture->draw(drawable);
//   else
      _window.draw(drawable);
}

void Renderer::drawLine(const Vec2f & from, const Vec2f & to, const sf::Color & color)
{
   sf::Vertex line[] =
   {
       sf::Vertex(from),
       sf::Vertex(to)
   };



   line[0].color = color;
   line[1].color = color;

   /*
   if(isRenderToTexture())
      _renderTexture->draw(line,2,sf::Lines);
   else
   */
      getWindow().draw(line, 2, sf::Lines);

}

Vec2f Renderer::getScreenMousePos() const
{
   return Vec2f(sf::Mouse::getPosition(getWindow()));
}

Vec2f Renderer::getGameMousePos() const
{
   return Vec2f(getWindow().mapPixelToCoords(sf::Mouse::getPosition(getWindow())));
}

Vec2f Renderer::gameToScreen(const Vec2f & gamePos) const
{
   return getWindow().mapCoordsToPixel(gamePos);
}

Vec2f Renderer::screenToGame(const Vec2f & screenPos) const
{
   return getWindow().mapPixelToCoords(Vec2i(screenPos.x, screenPos.y));
}

void Renderer::resetWindow()
{
   sf::ContextSettings settings = _window.getSettings();
   settings.antialiasingLevel = 2;//Config::get().antialiasingLevel;
   _window.create(sf::VideoMode(Config::get().windowWidht,
                                Config::get().windowHeight),
                  sf::String(Config::get().windowTitle),
                  sf::Style::Default,
                  settings);
   _window.setFramerateLimit(Config::get().fpsLimit);
   _window.setMouseCursorVisible(!Config::get().customCursor);

   resetCamera();
}

void Renderer::setWindowIcon(const sf::Image & image)
{
   _window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

Camera & Renderer::getCamera()
{
   return _camera;
}

void Renderer::updateCamera()
{
   _window.setView(getCamera());
}

void Renderer::resetCamera()
{
//   const sf::View & defaultCamera = _window.getDefaultView();
//   _camera.setCenter(defaultCamera.getCenter());
//   _camera.setSize(defaultCamera.getSize());

   _camera.setSize(Vec2f(_window.getSize()));
   _camera.setCenter(_window.getSize().x / 2.f,
                     _window.getSize().y / 2.f);
}

}
