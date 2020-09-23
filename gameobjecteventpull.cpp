#include "gameobjecteventpull.h"

std::list<GameObjectEventPull::Event> GameObjectEventPull::mEventList = std::list<Event>();
std::list<GameObjectEventPull::Event>::iterator GameObjectEventPull::mCurrentEvent = mEventList.begin();

GameObjectEventPull::EventTypes GameObjectEventPull::Event::type() const
{
  return mEventType;
}

SceneNode *GameObjectEventPull::Event::caller() const
{
  return mCaller;
}
