#ifndef OBS
#define OBD
#include "game_event.cpp"
class IObserver {
   public:
       virtual void Update(const GameEvent& event) = 0;
   };
#endif