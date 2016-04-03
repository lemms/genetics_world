// gw_behavior_factory.h

#ifndef GW_BEHAVIOR_FACTORY
#define GW_BEHAVIOR_FACTORY

namespace GeneticsWorld
{
    class Behavior;
    class CreatureTracker;
    class BehaviorFactory {
    public:
        BehaviorFactory(CreatureTracker* creature_tracker);
        Behavior* get_behavior_asexual_reproduction();
    private:
        CreatureTracker* _creature_tracker;
    };
}

#endif // GW_BEHAVIOR_FACTORY
