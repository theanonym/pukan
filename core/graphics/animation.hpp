#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"
#include "pukan/core/services/random.hpp"

namespace json { class Object; }

namespace pukan {

class Animation
{
public:
   Animation(const sf::Texture * texture,
             const Vec2i & beginPos,
             const Vec2i & frameSize,
             int frameNumber,
             float frameDelay,
             bool isLooped);

   Animation(const sf::Texture * texture,
             float frameDelay,
             bool isLooped,
             std::vector<Recti> frames);

   void update();

   unsigned getFrameId() const;
   unsigned getFrameCount() const;
   float getFrameDelay() const;
   void resetFrames();
   float getAnimationDuration() const;

   const sf::Texture * getCurrentTexture() const;
   const Recti & getCurrentFrameRect() const;

   static Animation * fromJson(const json::Object & jobj);
   json::Object toJson() const;

private:
   unsigned _index = 0;

   const sf::Texture * _texture;
   std::vector<Recti> _frameRects;

   float _frameDelay;
   bool  _isLooped;

   sf::Clock _timer;
};

}

#endif // ANIMATION_HPP
