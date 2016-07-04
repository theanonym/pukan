#include "pukan/core/entity.hpp"
#include "pukan/core/physics/body.hpp"
#include "pukan/core/physics/fixture.hpp"
#include "pukan/core/graphics/graphics.hpp"
#include "pukan/core/services/config.hpp"
#include "pukan/core/services/resources.hpp"
#include "json/jobject.hpp"

namespace pukan {

Entity::Entity(Body * body,
               Graphics * graphics,
               const std::string & name)
   : _body(body),
     _graphics(graphics),
     _name(name)
{
   _body->saveEntity(this);
}

Entity::~Entity()
{
   delete _graphics;
   delete _body;
}

void Entity::update()
{
//   getBody()->onUpdate();
   getGraphics()->update();
}

void Entity::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
   YOBA_UNUSED(renderStates);

   const Body * body = getBody();

   for(const std::unique_ptr<Fixture> & fixture : body->getFixtureList())
   {
      if(fixture->isSensor() && !Config::get().drawSensors)
         continue;

      const sf::Texture * texture     = getGraphics()->getTexture();
      const Recti & textureRect = getGraphics()->getTextureRect();

      sf::Shader * blur = Resources::get().getShader("blur");
//      blur->setParameter("texture", *texture);
//      blur->setParameter("blur_radius", Config::get().blurLevel);
//      blur->setParameter("blur_radius", 0.011);

      switch(fixture->getShape())
      {
         case Fixture::Polygon:
         {
            const b2PolygonShape * b2shape = dynamic_cast<const b2PolygonShape *>(fixture->getB2Shape());

            sf::ConvexShape polygon(b2shape->GetVertexCount());
            for(int i = 0; i < b2shape->GetVertexCount(); i++)
            {
               Vec2f v  = Vec2f::fromB2Pos(b2shape->GetVertex(i));
               if(Config::get().pixelFix)
               {
                  v.x += (v.x >= 0 ? 0.5 : -0.5);
                  v.y += (v.y >= 0 ? 0.5 : -0.5);
               }
               polygon.setPoint(i, v);
            }

            if(!fixture->isSensor())
            {
               polygon.setTexture(texture);
               polygon.setTextureRect(textureRect);
            }
            else
            {
               polygon.setFillColor(sf::Color::Transparent);
            }

            if(Config::get().drawOutline || fixture->isSensor())
            {
               polygon.setOutlineColor(sf::Color::Black);
               polygon.setOutlineThickness(-1);
            }
            polygon.setPosition(body->getPos());
            polygon.setRotation(body->getAngle());

            renderTarget.draw(polygon);

         } break;

         case Fixture::Rectangle:
         {
            Vec2f size = fixture->getRectangleSize();
            if(Config::get().pixelFix)
            {
               size.x += size.x >= 0 ? 0.5 : -0.5;
               size.y += size.y >= 0 ? 0.5 : -0.5;
            }

            float textureScaleX = size.x / textureRect.w;
            float textureScaleY = size.y / textureRect.h;

            sf::Sprite sprite(*texture, textureRect);
            sprite.setOrigin(size.x / textureScaleX / 2.f, size.y / textureScaleY / 2.f);
            sprite.setScale(textureScaleX, textureScaleY);
            sprite.setPosition(body->getPos());
            sprite.setRotation(body->getAngle());


            renderTarget.draw(sprite);

            if(Config::get().drawOutline && getGraphics()->hasOutline())
            {
               sf::RectangleShape outline(size);
               outline.setFillColor(sf::Color::Transparent);
               outline.setOutlineColor(sf::Color::Black);
               outline.setOutlineThickness(-1);
               outline.setOrigin(size.x / 2.f, size.y / 2.f);
               outline.setPosition(body->getPos());
               outline.setRotation(body->getAngle());

               renderTarget.draw(outline);
            }

//            sf::CircleShape cs;
//            cs.setFillColor(sf::Color::Red);
//            cs.setRadius(3);
//            cs.setOrigin(3, 3);
//            cs.setPosition(yoba(body->getPos() - fixture->getRectangleSize() / 2.f,
//                                body->getPos(),
//                                body->getAngle()));
//            renderTarget.draw(cs);
         } break;

         case Fixture::Circle:
         {
            float radius = fixture->getCircleRadius();
            if(Config::get().pixelFix)
               radius += 0.5;

            float textureScaleX = radius * 2.f / textureRect.w;
            float textureScaleY = radius * 2.f / textureRect.h;

            sf::Sprite sprite(*texture, textureRect);
            sprite.setOrigin(radius / textureScaleX, radius / textureScaleY);
            sprite.setScale(textureScaleX, textureScaleY);
            sprite.setPosition(body->getPos());
            sprite.setRotation(body->getAngle());

            renderTarget.draw(sprite);
         } break;
      }
   }

   if(Config::get().drawAABB)
   {
      Rectf aabb(body->getAABB());
      sf::RectangleShape rect(aabb.getSize());
      rect.setPosition(aabb.getPos());
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor(body->getB2Body()->IsAwake() ?
                              sf::Color::Red :
                              sf::Color::Blue);
      rect.setOutlineThickness(-1);
      renderTarget.draw(rect);
   }
}

Entity * Entity::clone() const
{
   return Entity::fromJson(getBody()->getWorld(), toJson());
}

Entity * Entity::fromJson(World * world, const json::Object & js)
{
   return new Entity(Body::fromJson(world, js.get("body")),
                     Graphics::fromJson(js.get("graphics")),
                     js.get<std::string>("name"));
}

json::Object Entity::toJson() const
{
   json::Object jentity(json::Object::Hash);
   jentity.add("name", getName());
   jentity.add("body", getBody()->toJson());
   jentity.add("graphics", getGraphics()->toJson());
   return jentity;
}

} // ns pukan
