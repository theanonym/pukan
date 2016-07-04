#include "pukan/core/graphics/animationmanager.hpp"
#include "json/jobject.hpp"

namespace pukan {

AnimationMgr::AnimationMgr(std::vector<Animation *> animations)
{
   for(Animation * animation : animations)
      _animations.push_back(std::unique_ptr<Animation>(animation));
}

AnimationMgr::AnimationMgr(Animation * animation)
   : AnimationMgr({ animation })
{
}

void AnimationMgr::update()
{
   getCurrentAnimation()->update();
}

unsigned AnimationMgr::getAnimationId() const
{
   return _index;
}

void AnimationMgr::setAnimationId(unsigned id)
{
   assert(id < getAnimationCount());
   _index = id;
   getAnimation(id)->resetFrames();
}

unsigned AnimationMgr::getAnimationCount() const
{
   return _animations.size();
}

void AnimationMgr::resetAnimations()
{
   _index = 0;
}

Animation * AnimationMgr::getCurrentAnimation() const
{
   assert(getAnimationId() < getAnimationCount());
   return _animations[getAnimationId()].get();
}

Animation * AnimationMgr::getAnimation(unsigned index) const
{
   assert(index < getAnimationCount());
   return _animations[index].get();
}

const sf::Texture * AnimationMgr::getCurrentTexture() const
{
   return getCurrentAnimation()->getCurrentTexture();
}

const Recti & AnimationMgr::getCurrentTextureRect() const
{
   return getCurrentAnimation()->getCurrentFrameRect();
}

AnimationMgr * AnimationMgr::fromJson(const json::Object & jobj)
{
   std::vector<Animation *> animations;
   for(const json::Object & janimation : jobj.get("animations").getArray())
      animations.push_back(Animation::fromJson(janimation));
   return new AnimationMgr(animations);
}

json::Object AnimationMgr::toJson() const
{
   json::Object janimationMgr(json::Object::Hash);

   json::Object janimations(json::Object::Array);
   for(const std::unique_ptr<Animation> & animation : _animations)
      janimations.add(animation->toJson());
   janimationMgr.add("animations", std::move(janimations));

   return janimationMgr;
}

}
