#ifndef FIXTURE_HPP
#define FIXTURE_HPP

#include "pukan/common.hpp"
#include "pukan/math/math.hpp"
#include "pukan/core/physics/physics.hpp"
#include "pukan/core/physics/filter.hpp"

namespace json { class Object; }

namespace pukan {

class Body;

class Fixture
{
   friend class Body;

public:
   enum Shape
   {
      Polygon,
      Rectangle,
      Circle
   };

   Fixture(b2Fixture * b2fixture);

   Body * getBody();
   const Body * getBody() const;
   Shape getShape() const;
   const Physics & getPhysics() const;
   const std::vector<Vec2f> getPolygonVertices() const;
   const Vec2f & getRectangleSize() const;
   float getCircleRadius() const;

   bool isSensor() const;
   void setSensor(bool value);

   Filter getFilter() const;
   void setFilter(const Filter & filter);

//protected:
   b2Fixture * getB2Fixture();
   const b2Fixture * getB2Fixture() const;
   const b2Shape * getB2Shape() const;



private:
   void saveShape(Shape shape);
   void savePhysics(const Physics & physics);
   void savePolygonVertices(const std::vector<Vec2f> & points);
   void saveRectangleSize(const Vec2f & size);
   void saveCircleRadius(float radius);

   json::Object toJson() const;

private:
   b2Fixture * _b2fixture = nullptr;

   Shape   _shape;
   Physics _physics;
   std::vector<Vec2f> _polygonVertices;
   Vec2f  _rectangleSize;
   float _circleRadius;
};

}

#endif // FIXTURE_HPP
