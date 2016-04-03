// gw_behavior_factory.cpp

#include "gw_creature_tracker.h"
#include "gw_behavior_reproduction.h"
#include "gw_behavior_factory.h"

GeneticsWorld::BehaviorFactory::BehaviorFactory(CreatureTracker* creature_tracker)
    : _creature_tracker(creature_tracker)
{
}

GeneticsWorld::Behavior* GeneticsWorld::BehaviorFactory::get_behavior_asexual_reproduction(float inheritance)
{
    CreatureTracker::BehaviorImpl* behavior_asexual_reproduction = new BehaviorAsexualReproductionImpl(_creature_tracker, inheritance);
    _creature_tracker->_behaviors.push_front(behavior_asexual_reproduction);
    return new Behavior(behavior_asexual_reproduction);
}
