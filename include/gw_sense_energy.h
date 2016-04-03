// gw_sense_energy.h

#ifndef GW_SENSE_ENERGY
#define GW_SENSE_ENERGY

#include "gw_creature_tracker.h"

namespace GeneticsWorld
{
    class SenseEnergyImpl : public CreatureTracker::SenseImpl {
    public:
        SenseEnergyImpl(CreatureTracker* creature_tracker);
        virtual ~SenseEnergyImpl();
        virtual float do_sense() const;
    };
}

#endif // GW_SENSE_ENERGY
