// gw_sense_energy.h

#ifndef GW_SENSE_ENERGY
#define GW_SENSE_ENERGY

#include "gw_creature_tracker.h"

namespace GeneticsWorld
{
    class SenseEnergyImpl : public CreatureTracker::SenseImpl {
    public:
        SenseEnergyImpl(CreatureTracker* creature_tracker, float inheritance);
        virtual ~SenseEnergyImpl();
        SenseEnergyImpl(const SenseEnergyImpl& other);
        virtual float do_sense();
        virtual std::string get_name() const;
        virtual CreatureTracker::SenseImpl* clone() const;
    };
}

#endif // GW_SENSE_ENERGY
