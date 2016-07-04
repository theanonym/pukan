#include "pukan/core/graphics/graphics.hpp"
#include "pukan/core/services/resources.hpp"
#include "pukan/core/services/random.hpp"
#include "json/jobject.hpp"

namespace pukan {

Graphics::Graphics(AnimationMgr * animationMgr)
   : _animationMgr(animationMgr)
{
}

Graphics::Graphics(const sf::Texture * staticTexture,
                   const Recti & textureRect,
                   bool hasOutline)
   : _staticTexture(staticTexture),
     _hasOutline(hasOutline)
{
   if(textureRect != Recti())
      _staticTextureRect = textureRect;
   else
      _staticTextureRect = Recti(0, 0,
                                       staticTexture->getSize().x,
                                       staticTexture->getSize().y);
}

Graphics::Graphics(const sf::Texture * staticTexture,
                   const Vec2f & bodySize,
                   bool hasOutline,
                   bool randomRect)
   : _staticTexture(staticTexture),
     _hasOutline(hasOutline)
{
   if(randomRect)
      _staticTextureRect = Recti(Random::get().getInt(0, int(staticTexture->getSize().x) - int(bodySize.x)),
                                       Random::get().getInt(0, int(staticTexture->getSize().y) - int(bodySize.y)),
                                       bodySize.x, bodySize.y);
   else
      _staticTextureRect = Recti(0, 0, bodySize.x, bodySize.y);
}

Graphics::~Graphics()
{
}

void Graphics::update()
{
   if(hasAnimation())
      _animationMgr->update();
}

bool Graphics::hasAnimation() const
{
   return !!_animationMgr;
}

AnimationMgr * Graphics::getAnimationMgr() const
{
   assert(hasAnimation());
   return _animationMgr.get();
}

const sf::Texture * Graphics::getTexture() const
{
   if(hasAnimation())
      return _animationMgr->getCurrentTexture();
   else
      return _staticTexture;
}

const Recti & Graphics::getTextureRect() const
{
   if(hasAnimation())
      return _animationMgr->getCurrentTextureRect();
   else
      return _staticTextureRect;
}

bool Graphics::hasOutline() const
{
   return _hasOutline;
}

Graphics * Graphics::fromJson(const json::Object & jobj)
{
   if(jobj.exists("animationMgr"))
      return new Graphics(AnimationMgr::fromJson(jobj.get("animationMgr")));
   else
      return new Graphics(Resources::get().getTexture(jobj.get<std::string>("staticTextureName")),
                          Recti::fromJson(jobj.get("staticTextureRect")),
                          jobj.get<bool>("hasOutline"));
}

json::Object Graphics::toJson() const
{
   json::Object jgraphics(json::Object::Hash);

   if(hasAnimation())
   {
      jgraphics.add("animationMgr", _animationMgr->toJson());
   }
   else
   {
      jgraphics.add("staticTextureName", Resources::get().getTextureName(_staticTexture));
      jgraphics.add("staticTextureRect", _staticTextureRect.toJson());
      jgraphics.add("hasOutline", hasOutline());
   }

   return jgraphics;
}

}
