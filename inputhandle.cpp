#include <assert.h>
#include <iostream>
#include <list>
#include "inputhandle.h"
#include "command.h"
#include "commandsimplementation.h"

InputHandle * InputHandle::mInputHandleInstanse = nullptr;

InputHandle::InputHandle()
  : mCommands(new std::list<Command*>()),
    mTurnUpButton(new TurnUp()),
    mTurnDownButton(new TurnDown()),
    mTurnLeftButton(new TurnLeft()),
    mTurnRightButton(new TurnRight())
{
  assert(mInputHandleInstanse == nullptr);
  mInputHandleInstanse = this;
}

std::shared_ptr<std::list<Command *> > InputHandle::processEvents() {
  if (mEvent.type == sf::Event::KeyPressed) {
      processKeyPressedEvents();
    }
  else if (mEvent.type == sf::Event::KeyReleased) {
      processKeyReleasedEvents();
    }
//  else if (m_Event.type == sf::Event::MouseMoved) {
//      processMouseMoveEvents(obj);
//    }

  if (!mPressedKeyBuffer.empty()) {
      return applyPressedKeys();
    }
  return nullptr;
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

//void InputHandle::processMouseMoveEvents(ControlableEntity *obj)
//{
//  m_MouseMoved->execute(obj, std::make_pair<double, double>(1,2));
//}

std::shared_ptr<std::list<Command*> > InputHandle::applyPressedKeys()
{
  (*mCommands).clear();


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

  return mCommands;
}
