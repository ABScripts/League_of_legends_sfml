#include "gamewindow.h"
#include "gamemodel.h"
#include "inputhandle.h"
#include <iostream>
#include "tank.h"
#include "tanktowerview.h"

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
  const std::vector<Tank> & tanks = m_gameModel_ptr->getTanks();
   for (const auto &tank: tanks) {

     }
}

void GameWindow::handleInput()
{
  std::vector<Tank> & tanks = m_gameModel_ptr->getTanks();
  m_InputHandler->processEvents(tanks[0]);
}

sf::Event &GameWindow::event()
{
  return m_InputHandler->event();
}
