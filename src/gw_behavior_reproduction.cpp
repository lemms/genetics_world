// gw_behavior_reproduction.cpp

#include <iostream>
#include <string>
#include "gw_behavior_reproduction.h"

GeneticsWorld::BehaviorAsexualReproductionImpl::BehaviorAsexualReproductionImpl(CreatureTracker* creature_tracker, float inheritance)
    : BehaviorImpl(creature_tracker, inheritance)
{
}

GeneticsWorld::BehaviorAsexualReproductionImpl::~BehaviorAsexualReproductionImpl()
{
}

GeneticsWorld::BehaviorAsexualReproductionImpl::BehaviorAsexualReproductionImpl(const BehaviorAsexualReproductionImpl& other)
    : BehaviorImpl(other._creature_tracker, other._inheritance)
{
}

void GeneticsWorld::BehaviorAsexualReproductionImpl::do_behavior()
{
    if (_behaviors_used() <= _max_behaviors_per_time_step())
    {
        _energy() -= 10.0f;
        _behaviors_used()++;
        _is_asexually_reproducing() = true;
        std::cout << "Reproducing asexually" << std::endl;
    }
}

std::string GeneticsWorld::BehaviorAsexualReproductionImpl::get_name() const
{
    return std::string("BehaviorAsexualReproduction");
}

GeneticsWorld::CreatureTracker::BehaviorImpl* GeneticsWorld::BehaviorAsexualReproductionImpl::clone() const
{
    return new BehaviorAsexualReproductionImpl(*this);
}
