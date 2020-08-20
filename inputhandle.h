#ifndef INPUTHANDLE_H
#define INPUTHANDLE_H

#include <set>
#include "SFML/Window/Event.hpp"

class Command;
class Tank;

class InputHandle
{
public:
  InputHandle();
  InputHandle(const InputHandle&) = delete;
  const InputHandle& operator=(const InputHandle&) = delete;
  void processEvents(Tank &obj);
  sf::Event &event();
private:
  std::set<sf::Keyboard::Key> m_PressedKeyBuffer;
  sf::Event m_Event;
  static InputHandle *m_InputHandleInstanse;
  Command *m_TurnUpButton;
  Command *m_TurnDownButton;
  Command *m_TurnLeftButton;
  Command *m_TurnRightButton;
private:
  void processKeyPressedEvents();
  void processKeyReleasedEvents();
  void applyPressedKeys(Tank &obj) const;
};

#endif // INPUTHANDLE_H
