#include "polygon.h"

Polygon::Polygon(int verticesCount) {
  mVertices.reserve(verticesCount);
}

int Polygon::size() const {
  return mVertices.size();
}

sf::Vector2f &Polygon::operator[](size_t index) {
  return mVertices[index];
}

void Polygon::push(sf::Vector2f vertice) {
  mVertices.push_back(vertice);
}
