// gw_sense_factory.cpp

#include "gw_creature_tracker.h"
#include "gw_sense_energy.h"
#include "gw_sense_factory.h"

GeneticsWorld::SenseFactory::SenseFactory(CreatureTracker* creature_tracker)
    : _creature_tracker(creature_tracker)
{
}

GeneticsWorld::Sense* GeneticsWorld::SenseFactory::get_sense_energy()
{
    CreatureTracker::SenseImpl* sense_energy_impl = new SenseEnergyImpl(_creature_tracker);
    _creature_tracker->_senses.push_front(sense_energy_impl);
    return new Sense(sense_energy_impl);
}
