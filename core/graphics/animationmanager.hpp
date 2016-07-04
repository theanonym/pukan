#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "pukan/common.hpp"
#include "pukan/core/graphics/animation.hpp"

namespace json { class Object; }

namespace pukan {

class AnimationMgr
{
public:
   AnimationMgr(std::vector<Animation *> animations);
   AnimationMgr(Animation * animation);

   void update();

   unsigned getAnimationId() const;
   void setAnimationId(unsigned id);
   unsigned getAnimationCount() const;
   void resetAnimations();

   Animation * getCurrentAnimation() const;
   Animation * getAnimation(unsigned index) const;

   sf::Texture const * getCurrentTexture() const;
   const Recti & getCurrentTextureRect() const;

   static AnimationMgr * fromJson(const json::Object & jobj);
   json::Object toJson() const;

private:
   unsigned _index = 0;

   std::vector<std::unique_ptr<Animation> > _animations;
};

}

#endif // ANIMATIONMANAGER_HPP
