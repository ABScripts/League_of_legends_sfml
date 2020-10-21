#ifndef GAMEOBJECTEVENTPULL_H
#define GAMEOBJECTEVENTPULL_H

#include <list>

class SceneNode;

class GameObjectEventPull
{
public:
  enum class EventTypes {
    RegisterInQuadTree
  };

  struct Event {
    Event(EventTypes eventType, SceneNode * caller)
      : mEventType(eventType),
        mCaller(caller) {}

    EventTypes type() const;
    SceneNode *caller() const;

  private:
    EventTypes mEventType;
    SceneNode * mCaller;
  };
public:
  GameObjectEventPull() = default;
  GameObjectEventPull(const GameObjectEventPull &) = delete;
  GameObjectEventPull &operator=(const GameObjectEventPull &) = delete;

  static void pushEvent(SceneNode * caller, EventTypes eventType) {
    mEventList.push_back(Event(eventType, caller));
  }

  static void eraseEvent(const std::list<Event>::iterator &toDelete) {
    mEventList.erase(toDelete);
  }

  static const Event &top() {
    return mEventList.front();
  }

  static bool empty() { return mEventList.empty(); }

  static int size() { return mEventList.size(); }

  static std::list<Event>::iterator begin() {
    return mEventList.begin();
  }

  static const std::list<Event>::iterator end() {
    return mEventList.end();
  }

  static const std::list<Event>::iterator increase() {
    return ++mCurrentEvent;
  }

  static const std::list<Event>::iterator decrease() {
    return  --mCurrentEvent;
  }

private:
  static std::list<Event> mEventList;
  static std::list<Event>::iterator mCurrentEvent;
};

#endif // GAMEOBJECTEVENTPULL_H
