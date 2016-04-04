// gw_sense_energy

#include <iostream>
#include <string>
#include "gw_sense_energy.h"

GeneticsWorld::SenseEnergyImpl::SenseEnergyImpl(CreatureTracker* creature_tracker,
                                                float inheritance)
    : SenseImpl(creature_tracker, inheritance)
{
}

GeneticsWorld::SenseEnergyImpl::~SenseEnergyImpl()
{
}

GeneticsWorld::SenseEnergyImpl::SenseEnergyImpl(const SenseEnergyImpl& other)
    : SenseImpl(other._creature_tracker, other._inheritance)
{
}

float GeneticsWorld::SenseEnergyImpl::do_sense()
{
    if (_senses_used() <= _max_senses_per_time_step())
    {
        _energy() -= 1.0f;
        _senses_used()++;
        std::cout << "Sensing energy: " << _energy() << std::endl;
        return _energy();
    }
    return 0.0f;
}

std::string GeneticsWorld::SenseEnergyImpl::get_name() const
{
    return std::string("SenseEnergy");
}

GeneticsWorld::CreatureTracker::SenseImpl* GeneticsWorld::SenseEnergyImpl::clone() const
{
    return new SenseEnergyImpl(*this);
}
