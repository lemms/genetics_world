// gw_world.h

#ifndef GW_WORLD
#define GW_WORLD

#include <list>

namespace GeneticsWorld
{
    class CreatureTracker;
    class BehaviorFactory;
    class SenseFactory;
    template <class Creature>
    class World {
    public:
        World();
        ~World();
        void add_creature();
        void time_step();
        void clear_dead_creatures();
        void spawn_born_creatures();
    private:
        typedef std::pair<Creature*, CreatureTracker*> CreaturePair;
        typedef std::list<CreaturePair>::iterator CreaturePairIterator;
        std::list<CreaturePair> _creatures;
        std::vector<std::list<CreaturePairIterator> > _grid;
        short _width;
        short _height;

        CreaturePair _spawn_new_creature_in_cell_with_parents(short cell, const CreatureTracker* lhs_parent, const CreatureTracker* rhs_parent);
        void _spawn_new_creature_in_cell_with_parent(short cell, const CreatureTracker* parent);
        void _spawn_new_creature_in_cell(short cell);
    };
}

template <class Creature>
GeneticsWorld::World() : _width(1000), _height(1000)
{
    _grid.resize(_width * _height);
}

template <class Creature>
GeneticsWorld::~World()
{
    for (CreaturePairIterator it = _creatures.begin(), it_end = _creatures.end();
         it != it_end; ++it)
    {
        delete it->first;
        delete it->second;
    }
    _creatures.clear();
}

template <class Creature>
void GeneticsWorld::add_creature()
{
    short cell = (rand() % _height) * _width + rand() % _width;
    _spawn_new_creature_in_cell(cell);
}

template <class Creature>
void GeneticsWorld::time_step()
{
    for (CreaturePairIterator it = _creatures.begin(), it_end = _creatures.end();
         it != it_end; ++it)
    {
        it->first->time_step();
        it->second->time_step();
    }
}

template <class Creature>
void GeneticsWorld::clear_dead_creatures()
{
    for (CreaturePairIterator it = _creatures.begin(), it_end = _creatures.end();
         it != it_end; ++it)
    {
        if (it->second->is_dead())
        {
            CreaturePairIterator it_delete = it;
            it++;
            delete it_delete->first;
            delete it_delete->second;
            short cell = it_delete->second.get_cell();
            std::list<CreaturePairIterator>:iterator grid_it =_grid[cell].find(it_delete);
            if (grid_it != _grid[cell].end())
            {
                _grid[cell].erase(grid_it);
            }
            else
            {
                std::cerr << "Error: Creature not found in grid cell" << cell << std::endl;
            }
            _creatures.erase(it_delete);
        }
    }
}

template <class Creature>
void GeneticsWorld::spawn_born_creatures()
{
    // spawn new asexual reproduction creatures
    short cell = 0;
    for (std::vector<std::list<CreaturePairIterator> > >::iterator g = _grid.begin(), g_end = _grid.end();
         g != g_end; ++g, ++cell)
    {
        for (std::list<CreaturePairIterator>::iterator l = g->begin(), l_end = g->end();
             l != l_end; ++l)
        {
            if ((*l)->second->is_asexually_reproducing())
            {
                _spawn_new_creature_in_cell_with_parent(cell, (*l)->second);
            }
        }
    }

    // spawn new sexual reproduction creatures
    cell = 0;
    for (std::vector<std::list<CreaturePairIterator> > >::iterator g = _grid.begin(), g_end = _grid.end();
         g != g_end; ++g, ++cell)
    {
        std::list<CreaturePairIterator> sexually_reproducing_creatures;
        for (std::list<CreaturePairIterator>::iterator l = g->begin(), l_end = g->end();
             l != l_end; ++l)
        {
            if ((*l)->second->is_sexually_reproducing())
            {
                sexually_reproducing_creatures.push_front(*l);
            }
        }
        while (sexually_reproducing_creatures.size() > 1)
        {
            short first_creature_index = rand() % sexually_reproducing_creatures.size();
            std::list<CreaturePairIterator>::iterator l = sexually_reproducing_creatures.begin();
            for (int i = 0; i < first_creature_index; ++i, ++l) {}
            CreaturePairIterator first_creature = *l;
            sexually_reproducing_creatures.erase(l);
            if (sexually_reproducing_creatures.empty())
            {
                break;
            }
            short second_creature_index = rand() % sexually_reproducing_creatures.size();
            l = sexually_reproducing_creatures.begin();
            for (int i = 0; i < second_creature_index; ++i, ++l) {}
            CreaturePairIterator second_creature = *l;
            sexually_reproducing_creatures.erase(l);
            _spawn_new_creature_in_cell_with_parents(cell, first_creature->second, second_creature->second);
        }
    }
}

template <class Creature>
CreaturePair GeneticsWorld::_spawn_new_creature_in_cell_with_parents(short cell, const CreatureTracker* lhs_parent, const CreatureTracker* rhs_parent)
{
    Creature* creature = new Creature;
    CreatureTracker* creature_tracker = new CreatureTracker(this, lhs_parent, rhs_parent);
    creature->setup(creature_tracker->get_behaviors(), creature_tracker->get_senses());
    CreaturePair creature_pair = std::make_pair(creature, creature_tracker);
    _creatures.push_front(creature_pair);
    _grid[cell].push_front(_creatures.begin());
    creature_pair.second->set_cell(cell);
    return creature_pair;
}

template <class Creature>
void GeneticsWorld::_spawn_new_creature_in_cell_with_parent(short cell, const CreatureTracker* lhs_parent)
{
    _spawn_new_creature_in_cell_with_parents(cell, lhs_parent, NULL);
}

template <class Creature>
void GeneticsWorld::_spawn_new_creature_in_cell(short cell)
{
    CreaturePair creature_pair = _spawn_new_creature_in_cell_with_parents(cell, NULL, NULL);
    BehaviorFactory behavior_factory(creature_pair.second);
    SenseFactory sense_factory(creature_pair.second);
    creature_pair.first->setup(behavior_factory, sense_factory);
}

#endif // GW_WORLD
