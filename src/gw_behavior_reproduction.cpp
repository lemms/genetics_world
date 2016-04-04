// gw_behavior_reproduction.cpp

#include <string>
#include "gw_behavior_reproduction.h"

GeneticsWorld::BehaviorAsexualReproductionImpl::BehaviorAsexualReproductionImpl(CreatureTracker* creature_tracker, float inheritance)
    : BehaviorImpl(creature_tracker, inheritance)
{
}

GeneticsWorld::BehaviorAsexualReproductionImpl::~BehaviorAsexualReproductionImpl()
{
}

void GeneticsWorld::BehaviorAsexualReproductionImpl::do_behavior() const
{
    if (_creature_tracker->_behaviors_used <= _creature_tracker->_max_behaviors_per_time_step)
    {
        _creature_tracker->_energy -= 10.0f;
        _creature_tracker->_behaviors_used++;
        _creature_tracker->_is_asexually_reproducing = true;
    }
}

std::string GeneticsWorld::BehaviorAsexualReproductionImpl::get_name() const
{
    return std::string("BehaviorAsexualReproduction");
}
