#include "gamewindow.h"
#include "gamemodel.h"
#include "inputhandle.h"
#include <iostream>
#include "tank.h"
#include "tanktowerview.h"
#include "test_entity_system/entity.h"
#include "command.h"

GameWindow::~GameWindow()
{
  delete m_gameModel_ptr;
}

GameWindow::GameWindow(const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
  : m_InputHandler(new InputHandle())
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    create(videoMode, title, style, settings);
    m_gameModel_ptr = new GameModel();
}

void GameWindow::render()
{
  const std::vector<Entity*> & tanks = m_gameModel_ptr->getTanks();

   for (const auto &tank: tanks) {
        draw(*tank);
     }
}

void GameWindow::handleInput() {
    mCommands = m_InputHandler->processEvents();
}

const sf::Event &GameWindow::event() const
{
  return m_InputHandler->event();
}

bool GameWindow::eventsHaveHappened()
{
  return sf::RenderWindow::pollEvent(m_InputHandler->event());
}

void GameWindow::update(const sf::Time &time)
{
    if (mCommands) {
  const std::vector<Entity*> & playerTank = m_gameModel_ptr->getTanks();


      for (auto & command : *mCommands) {
          if (const auto it = dynamic_cast<ControlableEntity*>(playerTank[0])) {
              command->execute(it, time);
        }
      }
    }
}
