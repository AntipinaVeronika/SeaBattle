enum class EventType { Save, Load, Input, Hit, Win, Loss, Start, SaveCompleted, LoadCompleted, Crime, Ab };
class GameEvent {
   public:
       EventType type;

       GameEvent(EventType t) : type(t) {}
   };
