#include "controlableentity.h"
#include "assetmanager.h"
#include "command.h"

ControlableEntity::ControlableEntity(Entity *parent)
  : Entity(parent)
{

}

void ControlableEntity::updateCurrent(const sf::Time &time, std::shared_ptr<std::list<Command *> > mCommands)
{
  if (mCommands) {
      for (auto & command : *mCommands) {
          command->execute(this, time);
        }
    }

}
