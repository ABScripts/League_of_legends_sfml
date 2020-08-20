#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "SFML/Graphics.hpp"

class GameModel;
class InputHandle;

class GameWindow : public sf::RenderWindow
{
public:
    GameWindow() = default;
    ~GameWindow();
    explicit GameWindow(const sf::String &title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings());

    void render();
    void handleInput();
    sf::Event &event();
private:
    GameModel *m_gameModel_ptr;
    InputHandle *m_InputHandler;
};

#endif // GAMEWINDOW_H
