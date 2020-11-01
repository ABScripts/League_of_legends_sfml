#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "SFML/System/Vector2.hpp"

struct Polygon {
  std::vector<sf::Vector2f> mVertices;

  Polygon(int verticesCount);


  int size() const;

  sf::Vector2f& operator[] (size_t index);

  void push(sf::Vector2f vertice);
};
#endif // POLYGON_H
