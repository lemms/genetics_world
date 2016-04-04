// gw_creature.h

namespace GeneticsWorld
{
    template <class Behavior, class Sense, class BehaviorFactory, class SenseFactory>
    class TestCreature {
    public:
        ~TestCreature();

        void setup(const BehaviorFactory& behavior_factory,
                   const SenseFactory& sense_factory);
        void setup(std::list<Behavior*> behaviors,
                   std::list<Sense*> senses);

        void time_step();
    private:
        std::map<std::string, Behavior*> _behaviors;
        std::map<std::string, Sense*> _senses;
    };
}

template <class Behavior, class Sense, class BehaviorFactory, class SenseFactory>
GeneticsWorld::TestCreature::~TestCreature()
{
    for (std::list<Behavior*>::const_iterator it = _behaviors.cbegin(), it_end = _behaviors.cend();
         it != it_end; ++it)
    {
        delete it->second;
    }
    for (std::list<Sense*>::const_iterator it = _senses.cbegin(), it_end = _senses.cend();
         it != it_end; ++it)
    {
        delete it->second;
    }
}

template <class Behavior, class Sense, class BehaviorFactory, class SenseFactory>
void GeneticsWorld::TestCreature::setup(const BehaviorFactory& behavior_factory,
                                        const SenseFactory& sense_factory)
{
    Behavior* behavior_asexual_reproduction = behavior_factory.get_behavior_asexual_reproduction();
    _behaviors.insert(std::make_pair(behavior_asexual_reproduction->get_name(), behavior_asexual_reproduction));
    Sense* sense_energy = sense_factory.get_sense_energy();
    _senses.insert(std::make_pair(sense_energy->get_name(), sense_energy));
}

template <class Behavior, class Sense, class BehaviorFactory, class SenseFactory>
void GeneticsWorld::TestCreature::setup(std::list<Behavior*> behaviors,
                                        std::list<Sense*> senses)
{
    for (std::list<Behavior*>::const_iterator it = behaviors.cbegin(), it_end = behaviors.cend();
         it != it_end; ++it)
    {
        _behaviors.insert(std::make_pair((*it)->get_name(), *it));
    }
    for (std::list<Sense*>::const_iterator it = senses.cbegin(), it_end = senses.cend();
         it != it_end; ++it)
    {
        _senses.insert(std::make_pair((*it)->get_name(), *it));
    }
}

template <class Behavior, class Sense, class BehaviorFactory, class SenseFactory>
void GeneticsWorld::TestCreature::time_step()
{
    if (_senses["SenseEnergy"].do_sense() > 0.0f)
    {
        _behaviors["BehaviorAsexualReproduction"].do_behavior();
    }
}
