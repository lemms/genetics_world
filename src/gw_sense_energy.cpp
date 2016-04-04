// gw_sense_energy

#include <string>
#include "gw_sense_energy.h"

GeneticsWorld::SenseEnergyImpl::SenseEnergyImpl(const CreatureTracker* creature_tracker,
                                                float inheritance)
    : SenseImpl(creature_tracker, inheritance)
{
}

GeneticsWorld::SenseEnergyImpl::~SenseEnergyImpl()
{
}

float GeneticsWorld::SenseEnergyImpl::do_sense() const
{
    if (_creature_tracker->_senses_used <= _creature_tracker->_max_senses_per_time_step)
    {
        _creature_tracker->_energy -= 1.0f;
        _creature_tracker->_senses_used++;
        return _creature_tracker->_energy;
    }
    return 0.0f;
}

std::string GeneticsWorld::SenseEnergyImpl::get_name() const
{
    return std::string("SenseEnergy");
}
