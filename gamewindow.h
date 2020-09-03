#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <list>
#include <memory>
#include "SFML/Graphics.hpp"

class Command;
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
    const sf::Event &event() const;
    bool eventsHaveHappened();
    void update(const sf::Time &time);
private:
    GameModel *m_gameModel_ptr;
    InputHandle *m_InputHandler;
    std::shared_ptr<std::list<Command*> > mCommands;
};

#endif // GAMEWINDOW_H
