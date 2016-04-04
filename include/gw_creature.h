// gw_creature.h

#include <list>
#include <map>

#include "gw_creature_tracker.h"

namespace GeneticsWorld
{
    class TestCreature {
    public:
        ~TestCreature();

        void setup(BehaviorFactory& behavior_factory,
                   SenseFactory& sense_factory);
        void setup(std::list<Behavior*> behaviors,
                   std::list<Sense*> senses);

        void time_step();
    private:
        std::map<std::string, Behavior*> _behaviors;
        std::map<std::string, Sense*> _senses;
    };
}
