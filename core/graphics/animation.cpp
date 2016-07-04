#include "pukan/core/graphics/animation.hpp"
#include "pukan/core/services/resources.hpp"
#include "json/jobject.hpp"

namespace pukan {

Animation::Animation(const sf::Texture * texture,
                     const Vec2i & beginPos,
                     const Vec2i & frameSize,
                     int frameNumber, float frameDelay,
                     bool isLooped)
   : _texture(texture),
     _frameDelay(frameDelay),
     _isLooped(isLooped)
{
   for(int i = 0; i < frameNumber; i++)
      _frameRects.push_back(Recti(beginPos.x + (frameSize.x * i),
                                        beginPos.y,
                                        frameSize.x - 1,
                                        frameSize.y - 1));
}

Animation::Animation(const sf::Texture * texture,
                     float frameDelay,
                     bool isLooped,
                     std::vector<Recti> frames)
   : _texture(texture),
     _frameRects(frames),
     _frameDelay(frameDelay),
     _isLooped(isLooped)
{
}

void Animation::update()
{
   if(_timer.getElapsedTime().asSeconds() >= _frameDelay)
   {
      if(_index < _frameRects.size() - 1)
         _index++;
      //FIXME Костыль
      else if(true||_isLooped)
         _index = 0;
      else
         ythrow(std::runtime_error, (b::format("Слишком мало кадров: %1%/%2%") % _index % _frameRects.size()).str());

      _timer.restart();
   }
}

unsigned Animation::getFrameId() const
{
   return _index;
}

unsigned Animation::getFrameCount() const
{
   return _frameRects.size();
}

float Animation::getFrameDelay() const
{
   return _frameDelay;
}

void Animation::resetFrames()
{
   _index = 0;
   _timer.restart();
}

float Animation::getAnimationDuration() const
{
   return _frameRects.size() * _frameDelay;
}

const sf::Texture * Animation::getCurrentTexture() const
{
   assert(_texture);
   return _texture;
}

const Recti & Animation::getCurrentFrameRect() const
{
   assert(_index < _frameRects.size());
   return _frameRects[_index];
}

Animation * Animation::fromJson(const json::Object & jobj)
{
   std::vector<Recti> frames;
   for(const json::Object & jframe : jobj.get("frames").getArray())
      frames.push_back(Recti::fromJson(jframe));

   return new Animation(Resources::get().getTexture(jobj.get<std::string>("textureName")),
                        jobj.get<float>("frameDelay"),
                        jobj.get<bool>("isLooped"),
                        frames);

}

json::Object Animation::toJson() const
{
   json::Object janimation(json::Object::Hash);
   janimation.add("textureName", Resources::get().getTextureName(_texture));
   janimation.add("frameDelay", _frameDelay);
   janimation.add("isLooped", _isLooped);

   json::Object jframes(json::Object::Array);
   for(const Recti & frame : _frameRects)
      jframes.add(frame.toJson());

   janimation.add("frames", jframes);

   return janimation;
}

}
