// gw_sense_energy.h

#ifndef GW_SENSE_ENERGY
#define GW_SENSE_ENERGY

#include "gw_creature_tracker.h"

namespace GeneticsWorld
{
    class SenseEnergyImpl : public CreatureTracker::SenseImpl {
    public:
        SenseEnergyImpl(const CreatureTracker* creature_tracker, float inheritance);
        virtual ~SenseEnergyImpl();
        virtual float do_sense() const;
        virtual std::string get_name() const;
    };
}

#endif // GW_SENSE_ENERGY
