#ifndef INPUTHANDLE_H
#define INPUTHANDLE_H

#include <set>
#include <memory>
#include <list>
#include "SFML/Window/Event.hpp"

class ControlableEntity;
class Command;
class Tank;
class TurnLeft;
class TurnRight;
class TurnUp;
class TurnDown;
class MouseMoved;
class MousePressed;

class InputHandle
{ 
public:
  InputHandle();
  InputHandle(const InputHandle&) = delete;
  const InputHandle& operator=(const InputHandle&) = delete;
  std::shared_ptr<std::list<Command*> > processEvents();
  sf::Event &event();
private:
  static InputHandle *mInputHandleInstanse;
  std::set<sf::Keyboard::Key> mPressedKeyBuffer;
  std::shared_ptr<std::list<Command*> > mCommands;
  sf::Event mEvent;
  TurnUp *mTurnUpButton;
  TurnDown *mTurnDownButton;
  TurnLeft *mTurnLeftButton;
  TurnRight *mTurnRightButton;
  MouseMoved *mMouseMoved;
  MousePressed *mMousePressed;
private:
  void processKeyPressedEvents();
  void processKeyReleasedEvents();
  void processMouseMoveEvents();
  void processMousePressedEvents();
  void commandsToApply();
};

#endif // INPUTHANDLE_H
