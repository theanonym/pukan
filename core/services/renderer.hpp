#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"
#include "pukan/singleton.hpp"
#include "pukan/core/services/camera.hpp"

namespace pukan {

class Renderer : public Singleton<Renderer>
{
public:
   Renderer();

   void fill(const sf::Color & color = sf::Color::White);
   void render();
   void close();

   void draw(const sf::Drawable & drawable);
   void drawLine(const Vec2f & from, const Vec2f & to, const sf::Color & color = sf::Color::Black);
   void drawRect(const Vec2f & pos, const Vec2f & size, const sf::Color & color, const sf::Color & outlineColor);
   void drawStrokeText(sf::Text & text, int offset = 1, const sf::Color & strokeColor = sf::Color::Black);

   Vec2f getScreenMousePos() const;
   Vec2f getGameMousePos() const;
   Vec2f gameToScreen(const Vec2f & gamePos) const;
   Vec2f screenToGame(const Vec2f & screenPos) const;

   //TODO убрать
   sf::RenderWindow & getWindow() { return _window; }
   const sf::RenderWindow & getWindow() const { return _window; }
   void resetWindow();

   void setWindowIcon(const sf::Image & image);

   Camera & getCamera();
   void updateCamera();
   void resetCamera();

private:
   sf::RenderWindow _window;
   Camera _camera;
};

}

#endif // RENDERER_HPP
