#ifndef INPUTHANDLE_H
#define INPUTHANDLE_H

#include <set>
#include <memory>
#include <list>
#include "SFML/Window/Event.hpp"

class ControlableEntity;
class Command;
class Tank;

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
  Command *mTurnUpButton;
  Command *mTurnDownButton;
  Command *mTurnLeftButton;
  Command *mTurnRightButton;
  Command *mMouseMoved;
private:
  void processKeyPressedEvents();
  void processKeyReleasedEvents();
  void processMouseMoveEvents(ControlableEntity *obj);
  std::shared_ptr<std::list<Command*> > applyPressedKeys();
};

#endif // INPUTHANDLE_H
