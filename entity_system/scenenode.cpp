#include "scenenode.h"
#include <algorithm>
#include <assert.h>
#include "tank.h"
#include <math.h>
#include "SFML/Graphics/Rect.hpp"
#include <algorithm>
#include "SFML/Graphics.hpp"
#include <qmath.h>

#include <string>
#include <vector>
#include <algorithm>


sf::Vector2f getRotated(sf::Rect<double> rect, sf::Vector2f around, float _Phi) {
//  auto Phi = _Phi * M_PI / 180;
  qreal Phi = qDegreesToRadians(_Phi);
  float x = (rect.left - around.x) * qCos(Phi) - (rect.top - around.y) * qSin(Phi) + around.x; // +?
  float y = (rect.left - around.x) * qSin(Phi) + (rect.top - around.y) * qCos(Phi) + around.y; // +?



  return {x, y};
}

sf::Vector2f getMidPoint(sf::Rect<double> rect, float _Phi) {
    qreal Phi = qDegreesToRadians(_Phi);
    float cosa = qCos(Phi);
    float sina = qSin(Phi);
    float wp = rect.width/2.f;
    float hp = rect.height/2.f;
    float px = rect.left + wp * cosa - hp * sina;
    float py = rect.top + wp * sina + hp * cosa;
    return {px, py};
}

struct Polygon {
  std::vector<sf::Vector2f> mVertices;

  Polygon(int verticesCount) {
    mVertices.reserve(verticesCount);
  }


  int size() const {
    return mVertices.size();
  }

  sf::Vector2f operator[] (size_t index) {
    return mVertices[index];
  }

  void push_back(sf::Vector2f &&vertice) {
    mVertices.push_back(vertice);
  }
};

bool overlap(Polygon polygon1, Polygon polygon2) {
	// // SEPARATING AXIS THEOREM:
	// If we find an axis that separates the both polygons, then the polygons cannot overlap! This works only for convex polygons!

	// Loop over the sides of first polygon
	for (int i = 0; i < polygon1.size()-1; i++)
	{
	// // construct normalized projection axis
		sf::Vector2f axis[2]			= {};
		sf::Vector2f perpendicular[2] = {};
		std::vector<double> projectionsA;
		std::vector<double> projectionsB;

		// compute axis of polygon sides
		axis->x = polygon1[i + 1].x - polygon1[i].x;
		axis->y = polygon1[i + 1].y - polygon1[i].y;

		// normalize vector
		double length_axis = sqrt(axis->x * axis->x + axis->y * axis->y);
		axis->x = axis->x / length_axis;
		axis->y = axis->y / length_axis;

		// find the perpendicular axis [x,y] = [-y,x]
		perpendicular->x = -axis->y;
		perpendicular->y =  axis->x;

		// // project all the points on the projection axis
		// Loop over vertices of 1st polygon
		for (int j = 0; j < polygon1.size(); j++)
		{
			// dot product maps vertices on 1D-axis
			double dot_product = polygon1[j].x * perpendicular->x + polygon1[j].y * perpendicular->y;
			projectionsA.push_back(dot_product);
		}
		// Loop over vertices of 2nd polygon
		for (int j = 0; j < polygon2.size(); j++)
		{
			// dot product maps vertices on 1D-axis
			double dot_product = polygon2[j].x * perpendicular->x + polygon2[j].y * perpendicular->y;
			projectionsB.push_back(dot_product);
		}

		// find min and max values of both projections of the polygons
		double minA, minB, maxA, maxB;
		minA = *std::min_element(projectionsA.begin(), projectionsA.end());
		maxA = *std::max_element(projectionsA.begin(), projectionsA.end());
		minB = *std::min_element(projectionsB.begin(), projectionsB.end());
		maxB = *std::max_element(projectionsB.begin(), projectionsB.end());


		if (maxA < minB || minA > maxB) {
			return false; // return false, if a separating axis is found and the polygons are not overlapping
		}
	} // end for-loop over the sides of 1st polygon

	// Loop over sides of second polygon
	for (int i = 0; i < polygon2.size() - 1; i++)
	{
	// // construct normalized projection axis
		sf::Vector2f axis[2] = {};
		sf::Vector2f perpendicular[2] = {};
		std::vector<double> projectionsA;
		std::vector<double> projectionsB;

		// compute axis of polygon sides
		axis->x = (double)polygon2[i + 1].x - (double)polygon2[i].x;
		axis->y = (double)polygon2[i + 1].y - (double)polygon2[i].y;

		// normalize vector
		double length_axis = sqrt(axis->x * axis->x + axis->y * axis->y);
		axis->x = axis->x / length_axis;
		axis->y = axis->y / length_axis;

		// find the perpendicular axis [x,y] = [-y,x]
		perpendicular->x = -axis->y;
		perpendicular->y = axis->x;

		// // project all the points on the projection axis
		// Loop over vertices of 1st polygon
		for (int j = 0; j < polygon1.size(); j++)
		{
			// dot product maps vertices on 1D-line
			double dot_product = polygon1[j].x * perpendicular->x + polygon1[j].y * perpendicular->y;
			projectionsA.push_back(dot_product);
		}
		// Loop over vertices of 2nd polygon
		for (int j = 0; j < polygon2.size(); j++)
		{
			// dot product maps vertices on 1D-line
			double dot_product = polygon2[j].x * perpendicular->x + polygon2[j].y * perpendicular->y;
			projectionsB.push_back(dot_product);
		}

		// find min and max values of both projections of the polygons
		double minA, minB, maxA, maxB;
		minA = *std::min_element(projectionsA.begin(), projectionsA.end());
		maxA = *std::max_element(projectionsA.begin(), projectionsA.end());
		minB = *std::min_element(projectionsB.begin(), projectionsB.end());
		maxB = *std::max_element(projectionsB.begin(), projectionsB.end());

		if (maxA < minB || minA > maxB) {
			return false; // return false, if a separating axis is found and the polygons are not overlapping
		}
	} // end for-loop over sides of 2nd polygon

  return true;
}

SceneNode::SceneNode()
  : mParentNode(nullptr)
{

}

SceneNode::~SceneNode() {
  for (auto child : mChildren) {
      delete child;
    }
}

void SceneNode::attachChild(SceneNode *child) {
  child->mParentNode = this;
  mChildren.push_back(std::move(child));
}

void SceneNode::attachToParent(SceneNode *child)
{
  if (mParentNode)
    mParentNode->attachChild(child);
}

SceneNode *SceneNode::detachChild(const SceneNode &node) {
  auto found = std::find_if(mChildren.begin(), mChildren.end(),
                            [&](SceneNode * cnode) -> bool { return cnode == &node; } ); // check whether that node is in children vect
  assert(found != mChildren.end());                                                      // check is it really is there
  SceneNode * result = std::move(*found);                                                // getting that child in an. var
  result->mParentNode = nullptr;
  mChildren.erase(found);                                                                // deleting from this node's children vect
  return result;                                                                         // return it so we could attach that node to some else node
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  drawCurrent(target, states);

  for (const auto &child : mChildren) {
      child->draw(target, states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}

void SceneNode::update(const sf::Time &time)
{
  updateCurrent(time);
  for (const auto &child : mChildren) {
      child->update(time);
    }
}

void SceneNode::updateCurrent(const sf::Time &time)
{

}

sf::Transform SceneNode::getWorldTransform() const
{
  sf::Transform t(getTransform());
  if (mParentNode) { // while we are not actually getting the layer`s transform matrix
      t *= mParentNode->getWorldTransform();
    }
  return t;
}

void SceneNode::checkNodeCollisions(SceneNode *other, std::vector<std::pair<SceneNode *, SceneNode *> > &collisionPairs)
{
  if (other != this) {
      // check for children
      for (auto &entityOnLayer : other->mChildren) { // loop through layer`s children
          if (entityOnLayer != this) {
              if (intersects(*this, *entityOnLayer)) {
                  collisionPairs.push_back(std::pair<SceneNode*, SceneNode*>(this, entityOnLayer));
                }
              // else, if collision is not detected see for them in deeper "layers"
              this->checkNodeCollisions(entityOnLayer, collisionPairs);}
        }
      if (intersects(*other, *this)) { // check collision for the father
          collisionPairs.push_back(std::pair<SceneNode*, SceneNode*>(this, other));
        }
    }
}

void SceneNode::checkSceneCollisions(SceneNode *other, std::vector<std::pair<SceneNode *, SceneNode *> > &collisionPairs) {
  checkNodeCollisions(other, collisionPairs);

  for (auto &entityOnLayer : other->mChildren) {
      checkNodeCollisions(entityOnLayer, collisionPairs);
    }
}

bool SceneNode::isDestroyed() const
{
  return mIsDestroyed;
}

bool SceneNode::intersects(const SceneNode &lhr, const SceneNode &rhs)
{
  if (dynamic_cast<const Tank*>(&lhr) && dynamic_cast<const Tank*>(&rhs)) {
    auto t1 = dynamic_cast<const Tank*>(&lhr);
    auto t2 = dynamic_cast<const Tank*>(&rhs);

    auto r2 = rhs.getBoundingRect();
    decltype (lhr.getRotation()) ang2 = /*360 -*/ rhs.getRotation();
    sf::Vector2f ar2 = /*getMidPoint(sf::Rect<double>(r2.left, r2.top, r2.width, r2.height), ang2);*/ t2->getCenterPoint();
    Polygon pointspoly2(4);
    pointspoly2.push_back(sf::Vector2f(r2.left, r2.top));
    pointspoly2.push_back(getRotated(sf::Rect<double>(r2.left + r2.width, r2.top, r2.width, r2.height), ar2, ang2));
    pointspoly2.push_back(getRotated(sf::Rect<double>(r2.left + r2.width, r2.top + r2.height, r2.width, r2.height), ar2, ang2));
    pointspoly2.push_back(getRotated(sf::Rect<double>(r2.left, r2.top + r2.height, r2.width, r2.height), ar2, ang2));


      auto r1 = lhr.getBoundingRect();
      decltype (lhr.getRotation()) ang = /*360 - */lhr.getRotation();
      sf::Vector2f ar1 = /*getMidPoint(sf::Rect<double>(r1.left, r1.top, r1.width, r1.height), ang);*/ t1->getCenterPoint();
      Polygon pointspoly1(4);
      pointspoly1.push_back(sf::Vector2f(r1.left, r1.top));
      pointspoly1.push_back(getRotated(sf::Rect<double>(r1.left + r1.width, r1.top, r1.width, r1.height), ar1, ang));
      pointspoly1.push_back(getRotated(sf::Rect<double>(r1.left + r1.width, r1.top + r1.height, r1.width, r1.height), ar1, ang));
      pointspoly1.push_back(getRotated(sf::Rect<double>(r1.left, r1.top + r1.height, r1.width, r1.height), ar1, ang));


      qDebug() << "Polygon 1: \n";
      for (int i = 0; i < pointspoly1.size(); ++i) {
          qDebug() << pointspoly1[i].x << "  " << pointspoly1[i].y << "\n";
        }



      qDebug() << "Polygon 2: \n";
      for (int i = 0; i < pointspoly1.size(); ++i) {
          qDebug() << pointspoly2[i].x << "  " << pointspoly2[i].y << "\n";
        }

      return overlap(pointspoly1, pointspoly2);
    }
  return false;
 //return lhr.getBoundingRect().intersects(rhs.getBoundingRect());
}
