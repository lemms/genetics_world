// gw_behavior_reproduction.h

#ifndef GW_BEHAVIOR_REPRODUCTION
#define GW_BEHAVIOR_REPRODUCTION

#include "gw_creature_tracker.h"

namespace GeneticsWorld
{
    class BehaviorAsexualReproductionImpl : public CreatureTracker::BehaviorImpl {
    public:
        BehaviorAsexualReproductionImpl(CreatureTracker* creature_tracker, float inheritance);
        virtual ~BehaviorAsexualReproductionImpl();
        virtual void do_behavior();
    }
}

#endif // GW_BEHAVIOR_REPRODUCTION
