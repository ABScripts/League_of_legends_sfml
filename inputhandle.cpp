#include <assert.h>
#include <list>
#include "inputhandle.h"
#include "mousecommand.h"
#include "commandsimplementation.h"

InputHandle * InputHandle::mInputHandleInstanse = nullptr;

InputHandle::InputHandle()
  : mCommands(new std::list<Command*>()),
    mTurnUpButton(new TurnUp()),
    mTurnDownButton(new TurnDown()),
    mTurnLeftButton(new TurnLeft()),
    mTurnRightButton(new TurnRight()),
    mMouseMoved(new MouseMoved()),
    mMousePressed(new MousePressed())
{
  assert(mInputHandleInstanse == nullptr);
  mInputHandleInstanse = this;
}

std::shared_ptr<std::list<Command *> > InputHandle::processEvents() {
  (*mCommands).clear();

  if (mEvent.type == sf::Event::KeyPressed) {
      processKeyPressedEvents();
    }
  else if (mEvent.type == sf::Event::KeyReleased) {
      processKeyReleasedEvents();
    }
  else if (mEvent.type == sf::Event::MouseMoved) {
      processMouseMoveEvents();
    }
  else if (mEvent.type == sf::Event::MouseButtonPressed) {
      processMousePressedEvents();
    }

  if (!mPressedKeyBuffer.empty()) {
      commandsToApply();
    }

  return mCommands;
}

sf::Event &InputHandle::event() {
  return mEvent;
}

void InputHandle::processKeyPressedEvents() {
  if (mPressedKeyBuffer.find(mEvent.key.code) == mPressedKeyBuffer.end()) { // if it is a new key pressing
      mPressedKeyBuffer.insert(mEvent.key.code);
    }
}

void InputHandle::processKeyReleasedEvents() {
  auto it = mPressedKeyBuffer.find(mEvent.key.code);
  if (it != mPressedKeyBuffer.end()) { // if this key pressing is active
      mPressedKeyBuffer.erase(it);
    }
}

void InputHandle::processMouseMoveEvents()
{
 mMouseMoved->setMousePosition(sf::Vector2f(mEvent.mouseMove.x, mEvent.mouseMove.y));
 mCommands->push_back(mMouseMoved);
}

void InputHandle::processMousePressedEvents()
{
  mMousePressed->setMousePosition(sf::Vector2f(mEvent.mouseMove.x, mEvent.mouseMove.y));
  mCommands->push_back(mMousePressed);
}

void InputHandle::commandsToApply()
{
  for (const auto &key : mPressedKeyBuffer) {
      if (key == sf::Keyboard::Left) {
          mCommands->push_back(mTurnLeftButton);
        }
      else if (key == sf::Keyboard::Right) {
          mCommands->push_back(mTurnRightButton);
        }
       else if (key == sf::Keyboard::Up) {
          mCommands->push_back(mTurnUpButton);
        }
      else if (key == sf::Keyboard::Down) {
          mCommands->push_back(mTurnDownButton);
        }
    }
}
