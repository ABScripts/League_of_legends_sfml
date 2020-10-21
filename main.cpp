#include "game.h"
#define DEBUG
#include "mathcore.h"

int main()
{
//  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     int x = 0, y = 0, w = 100, h = 100;
//     sf::ConvexShape convex;
//     convex.setPointCount(4);
//     convex.setPosition(0, 0);
//     convex.setFillColor(sf::Color::Red);

//     convex.setPoint(0, sf::Vector2f(x, y));
//     convex.setPoint(1, sf::Vector2f(x + w, y));
//     convex.setPoint(2, sf::Vector2f(x + w, y + h));
//     convex.setPoint(3, sf::Vector2f(x, y + h));
//     convex.setOrigin(0,0);
//    int dx = 5, dy = 5;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if (event.type == sf::Event::KeyPressed) {
//                 if (event.key.code == sf::Keyboard::Up) {
//                     const auto shift = MathCore::getLineMoveCoefficients(convex.getRotation(), dx); // consider changing these lines to more readable ones
//                     sf::Vector2 mVelocityVector = {dx, -dy};
//                     convex.move(mVelocityVector.x, mVelocityVector.y);
//                   }
//                 if (event.key.code == sf::Keyboard::Down) {
//                     const auto shift = MathCore::getLineMoveCoefficients(convex.getRotation(), dx); // consider changing these lines to more readable ones
//                     sf::Vector2 mVelocityVector = {-dx, dy};
//                     convex.move(mVelocityVector.x, mVelocityVector.y);
//                   }
//                 if (event.key.code == sf::Keyboard::Right) {
//convex.setRotation(convex.getRotation() + 10);
//                   }
//                 if (event.key.code == sf::Keyboard::Left) {
//convex.setRotation(convex.getRotation() + 10);
//                   }
//               }
//         }

//         window.clear();
//         window.draw(convex);
//         window.display();
//     }

  Game game;
  game.run();
}
