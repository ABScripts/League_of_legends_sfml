#include <assert.h>
#include <iostream>
#include "inputhandle.h"
#include "command.h"
#include "commandsimplementation.h"

InputHandle * InputHandle::m_InputHandleInstanse = nullptr;

InputHandle::InputHandle()
  : m_TurnUpButton(new TurnUp()),
    m_TurnDownButton(new TurnDown()),
    m_TurnLeftButton(new TurnLeft()),
    m_TurnRightButton(new TurnRight())
{
  assert(m_InputHandleInstanse == nullptr);
  m_InputHandleInstanse = this;
}

void InputHandle::processEvents(ControlableEntity *obj) {
  if (m_Event.type == sf::Event::KeyPressed) {
      processKeyPressedEvents();
    }
  else if (m_Event.type == sf::Event::KeyReleased) {
      processKeyReleasedEvents();
    }
//  else if (m_Event.type == sf::Event::MouseMoved) {
//      processMouseMoveEvents(obj);
//    }

  if (!m_PressedKeyBuffer.empty()) {
      applyPressedKeys(obj);
    }
}

sf::Event &InputHandle::event() {
  return m_Event;
}

void InputHandle::processKeyPressedEvents() {
  if (m_PressedKeyBuffer.find(m_Event.key.code) == m_PressedKeyBuffer.end()) { // if it is a new key pressing
      m_PressedKeyBuffer.insert(m_Event.key.code);
    }
}

void InputHandle::processKeyReleasedEvents() {
  auto it = m_PressedKeyBuffer.find(m_Event.key.code);
  if (it != m_PressedKeyBuffer.end()) { // if this key pressing is active
      m_PressedKeyBuffer.erase(it);
    }
}

//void InputHandle::processMouseMoveEvents(ControlableEntity *obj)
//{
//  m_MouseMoved->execute(obj, std::make_pair<double, double>(1,2));
//}

void InputHandle::applyPressedKeys(ControlableEntity *obj) const
{
  for (const auto &key : m_PressedKeyBuffer) {
      if (key == sf::Keyboard::Left) {
          m_TurnLeftButton->execute(obj);
        }
      else if (key == sf::Keyboard::Right) {
          m_TurnRightButton->execute(obj);
        }
       else if (key == sf::Keyboard::Up) {
         m_TurnUpButton->execute(obj);
        }
      else if (key == sf::Keyboard::Down) {
          m_TurnDownButton->execute(obj);
        }
    }
}
