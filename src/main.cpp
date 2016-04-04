#include <iostream>

#include "genetics_world.h"
#include "gw_driver.h"
#include "gw_world.h"
#include "gw_creature.h"

int main(int argc, char** argv)
{
    std::cout << "Genetics world v" <<
                 GENETICS_WORLD_VERSION_MAJOR << "." <<
                 GENETICS_WORLD_VERSION_MINOR << std::endl;

    srand(12345);

    GeneticsWorld::Driver<GeneticsWorld::TestCreature, GeneticsWorld::World> driver;
    driver.setup();
    for (size_t t = 0; t < 10000; ++t)
    {
        driver.time_step();
    }
    return 0;
}
