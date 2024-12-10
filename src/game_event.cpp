enum class EventType { Save, Load, Input, Hit, Win, Loss, Start, SaveCompleted, LoadCompleted, Crime, Ab };
class GameEvent {
   public:
       EventType type;
       // Добавьте дополнительные параметры, если необходимо

       GameEvent(EventType t) : type(t) {}
   };