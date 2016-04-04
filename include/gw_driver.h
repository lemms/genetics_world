// gw_driver.h

#ifndef GW_DRIVER
#define GW_DRIVER

namespace GeneticsWorld
{
    template <class Creature, template <class> class World>
    class Driver {
    public:
        Driver();
        ~Driver();
        void setup();
        void time_step();
    private:
        World<Creature> _world;
    };
};

template <class Creature, template <class> class World>
GeneticsWorld::Driver<Creature, World>::Driver()
{
}

template <class Creature, template <class> class World>
GeneticsWorld::Driver<Creature, World>::~Driver()
{
}

template <class Creature, template <class> class World>
void GeneticsWorld::Driver<Creature, World>::setup()
{
    for (size_t c = 0; c < 100; ++c)
    {
        _world.add_creature();
    }
}

template <class Creature, template <class> class World>
void GeneticsWorld::Driver<Creature, World>::time_step()
{
    _world.time_step();
    _world.clear_dead_creatures();
    _world.spawn_born_creatures();
}

#endif // GW_DRIVER
