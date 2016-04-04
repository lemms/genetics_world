// gw_sense_factory.h

#ifndef GW_SENSE_FACTORY
#define GW_SENSE_FACTORY

namespace GeneticsWorld
{
    class Sense;
    class CreatureTracker;
    class SenseFactory {
    public:
        SenseFactory(CreatureTracker* creature_tracker);
        Sense* get_sense_energy(float inheritance);
    private:
        CreatureTracker* _creature_tracker;
    };
}

#endif // GW_SENSE_FACTORY
