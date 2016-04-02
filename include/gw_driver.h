// gw_driver.h

#ifndef GW_DRIVER
#define GW_DRIVER

namespace GeneticsWorld
{
    template <class Creature, template <class> World>
    class Driver {
    public:
        Driver();
        ~Driver();
        void setup();
        void time_step();
    private:
        World _world;
    };
};

template <class Creature, template <class> World>
GeneticsWorld::Driver::Driver()
{
}

template <class Creature, template <class> World>
GeneticsWorld::Driver::~Driver()
{
}

template <class Creature, template <class> World>
void GeneticsWorld::Driver::setup()
{
    for (size_t c = 0; c < 100; ++c)
    {
        _world.add_creature();
    }
}

template <class Creture, template <class> World>
void GeneticsWorld::Driver::time_step()
{
    world.time_step();
    world.clear_dead_creatures();
    world.spawn_born_creatures();
}

#endif // GW_DRIVER
