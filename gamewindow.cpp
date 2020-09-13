#include "gamewindow.h"
#include "gamemodel.h"
#include "inputhandle.h"
#include "command.h"
#include "entity_system/entity.h"
#include "tank.h"

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
  const auto & gameLayers = m_gameModel_ptr->getLayers();

  for (const auto &layer : gameLayers) {
      draw(*layer.second);
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
      Tank * playerTank = m_gameModel_ptr->getPlayer();
      playerTank->updateCurrent(time, mCommands);
    }

    for (const auto & layer : m_gameModel_ptr->getLayers()) {
        layer.second->update(time);
    }
}
