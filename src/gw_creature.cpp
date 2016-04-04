// gw_creature.cpp

#include <iostream>
#include "gw_behavior_factory.h"
#include "gw_sense_factory.h"
#include "gw_creature.h"

GeneticsWorld::TestCreature::~TestCreature()
{
    for (std::map<std::string, Behavior*>::const_iterator it = _behaviors.cbegin(), it_end = _behaviors.cend();
         it != it_end; ++it)
    {
        delete it->second;
    }
    for (std::map<std::string, Sense*>::const_iterator it = _senses.cbegin(), it_end = _senses.cend();
         it != it_end; ++it)
    {
        delete it->second;
    }
}

void GeneticsWorld::TestCreature::setup(BehaviorFactory& behavior_factory,
                                        SenseFactory& sense_factory)
{
    Behavior* behavior_asexual_reproduction = behavior_factory.get_behavior_asexual_reproduction(10.0f);
    _behaviors.insert(std::make_pair(behavior_asexual_reproduction->get_name(), behavior_asexual_reproduction));
    Sense* sense_energy = sense_factory.get_sense_energy(10.0f);
    _senses.insert(std::make_pair(sense_energy->get_name(), sense_energy));
}

void GeneticsWorld::TestCreature::setup(std::list<Behavior*> behaviors,
                                        std::list<Sense*> senses)
{
    for (std::list<Behavior*>::const_iterator it = behaviors.cbegin(), it_end = behaviors.cend();
         it != it_end; ++it)
    {
        std::cout << "Adding behavior: " << (*it)->get_name() << std::endl;
        _behaviors.insert(std::make_pair((*it)->get_name(), *it));
    }
    for (std::list<Sense*>::const_iterator it = senses.cbegin(), it_end = senses.cend();
         it != it_end; ++it)
    {
        std::cout << "Adding sense: " << (*it)->get_name() << std::endl;
        _senses.insert(std::make_pair((*it)->get_name(), *it));
    }
}

void GeneticsWorld::TestCreature::time_step()
{
    if (_senses.find("SenseEnergy") != _senses.end() && _senses["SenseEnergy"]->do_sense() > 0.0f)
    {
        if (_behaviors.find("BehaviorAsexualReproduction") != _behaviors.end())
        {
            _behaviors["BehaviorAsexualReproduction"]->do_behavior();
        }
    }
}
