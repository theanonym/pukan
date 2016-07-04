#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "pukan/common.hpp"
#include "pukan/core/graphics/animationmanager.hpp"
#include "pukan/math/math.hpp"

namespace json { class Object; }

namespace pukan {

class Graphics
{
public:
   Graphics(AnimationMgr * animationMgr);
   Graphics(const sf::Texture * staticTexture,
            const Recti & textureRect = Recti(), \
            bool hasOutline = true);

   Graphics(const sf::Texture * staticTexture,
            const Vec2f & bodySize,
            bool hasOutline = true,
            bool randomRect = false);
   ~Graphics();

   void update();

   bool hasAnimation() const;
   AnimationMgr * getAnimationMgr() const;
   const sf::Texture * getTexture() const;
   const Recti & getTextureRect() const;
   bool hasOutline() const;

   static Graphics * fromJson(const json::Object & jobj);
   json::Object toJson() const;

private:
   const sf::Texture * _staticTexture;
   Recti _staticTextureRect;
   bool _hasOutline = false;

   std::unique_ptr<AnimationMgr> _animationMgr;
};

}

#endif // GRAPHICS_HPP
