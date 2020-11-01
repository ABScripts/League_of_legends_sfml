#include "gamewindow.h"
#include "gamemodel.h"
#include "inputhandle.h"
#include "command.h"
#include "entity_system/entity.h"
#include "tank.h"
#include "bullet.h"
#include "gameobjecteventpull.h"

class Event;

GameWindow::GameWindow(const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
  : m_InputHandler(new InputHandle())
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    create(videoMode, title, style, settings);
    m_gameModel_ptr = new GameModel(*this); // the map size should be passed
}

GameWindow::~GameWindow()
{
  delete m_gameModel_ptr;
  delete m_InputHandler;
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

void GameWindow::updateGameModel(const sf::Time &time)
{
  m_gameModel_ptr->update(*this, mCommands, time);
}

void GameWindow::processPullEvents()
{
  using EventType = GameObjectEventPull::EventTypes;

  for (auto event = GameObjectEventPull::begin();
       event != GameObjectEventPull::end();
       event = GameObjectEventPull::increase())
    {
      if (event->type() == EventType::RegisterInQuadTree) {
          m_gameModel_ptr->insertInQuadTree(event->caller(), *this);
        }
    }
}

void GameWindow::setPossibleCollisionPairs()
{
  std::vector<std::vector<SceneNode*>> objectsInTreeLayers;
  m_gameModel_ptr->getGameObjectsByTreeLayers(objectsInTreeLayers);

  for (size_t i = 0; i < objectsInTreeLayers.size(); ++i) {
      m_gameModel_ptr->retrieve(objectsInTreeLayers[i], objectsInTreeLayers[i][0]);
    }

  for (auto & subObjectCollection : objectsInTreeLayers) {
      for (size_t i = 0; i < subObjectCollection.size(); ++i) {
          for (size_t j = 0; j < subObjectCollection.size(); ++j) {
              subObjectCollection[i]->checkNodeCollisions(subObjectCollection[j], mCollisionPairs);
            }
        }
    }
}

void GameWindow::processCollisions()
{
  setPossibleCollisionPairs();

  for (auto &collisionPair : mCollisionPairs) {
    if (!collisionPair.first->isDestroyed() && !collisionPair.second->isDestroyed()) {
        collisionPair.second->applyCollisionToSelf(collisionPair.first);
     }
    }

  mCollisionPairs.clear();
}

bool GameWindow::eventsHaveHappened()
{
  return sf::RenderWindow::pollEvent(m_InputHandler->event());
}

void GameWindow::update(const sf::Time &time)
{
  updateGameModel(time);
  processPullEvents();
  processCollisions();
}



