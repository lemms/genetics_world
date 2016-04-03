// gw_creature_tracker.h

#ifndef GW_CREATURE_TRACKER
#define GW_CREATURE_TRACKER

namespace GeneticsWorld
{
    class CreatureTracker
    {
    public:
        CreatureTracker(short cell, const CreatureTracker* lhs_parent, const CreatureTracker* rhs_parent);
        ~CreatureTracker();
        CreatureTracker(const CreatureTracker& other);
        CreatureTracker& operator=()(const CreatureTracker& other);

        BehaviorFactory& get_behavior_factory();
        SenseFactory&    get_sense_factory();
        
        bool is_asexually_reproducing();
        bool is_sexually_reproducing();

        void time_step();

        short get_cell() const;

        class Behavior {
        public:
            virtual ~Behavior() {}
            virtual void do_behavior() = 0;
        };

        class Sense {
        public:
            virtual ~Sense() {}
            virtual float do_sense() = 0;
        };

        class BehaviorFactory;
        class SenseFactory;
    private:
        short _life_span;
        float _energy;
        short _behaviors_used;
        short _senses_used;
        short _max_behaviors_per_time_step;
        short _max_senses_per_time_step;
        bool _is_asexually_reproducing;
        bool _is_sexually_reproducing;
        short _cell;

        BehaviorFactory _behavior_factory;
        SenseFactory _sense_factory;

        std::list<Behavior*> _behaviors;
        std::list<Sense*> _senses;
    };
}

GeneticsWorld::CreatureTracker::CreatureTracker(short cell,
                                                const CreatureTracker* lhs_parent,
                                                const CreatureTracker* rhs_parent)
    : _life_span(100),
      _energy(100.0f),
      _behaviors_used(0),
      _senses_used(0),
      _max_behaviors_per_time_step(2),
      _max_senses_per_time_step(2),
      _is_asexually_reproducing(false),
      _is_sexually_reproducing(false),
      _cell(cell),
      _behavior_factory(this),
      _sense_factory(this)
{
}

GeneticsWorld::CreatureTracker::~CreatureTracker()
{
    for (std::list<Behavior*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
         it != it_end; ++it)
    {
        delete *it;
    }
    for (std::list<Sense*>::iterator it = _senses.begin(), it_end = _senses.end();
         it != it_end; ++it)
    {
        delete *it;
    }
}

GeneticsWorld::CreatureTracker::CreatureTracker(const CreatureTracker& other)
{
    _life_span = other._life_span;
    _energy = other._life_span;
    _behaviors_used = other._behaviors_used;
    _senses_used = other._senses_used;
    _max_behaviors_per_time_step = other._max_behaviors_per_time_step;
    _max_senses_per_time_step = other._max_senses_per_time_step;
    _is_asexually_reproducing = other._is_asexually_reproducing;
    _is_sexually_reproducing = other._is_sexually_reproducing;
    _cell = other._cell;
    for (std::list<Behavior*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
         it != it_end; ++it)
    {
        _behaviors.push_front(new Behavior(*it));
    }
    for (std::list<Sense*>::iterator it = _senses.begin(), it_end = _senses.end();
         it != it_end; ++it)
    {
        _senses.push_front(new Sense(*it));
    }
}

GeneticsWorld::CreatureTracker& GeneticsWorld::CreatureTracker::operator=(const CreatureTracker& other)
{
    if (this != &other)
    {
        _life_span = other._life_span;
        _energy = other._life_span;
        _behaviors_used = other._behaviors_used;
        _senses_used = other._senses_used;
        _max_behaviors_per_time_step = other._max_behaviors_per_time_step;
        _max_senses_per_time_step = other._max_senses_per_time_step;
        _is_asexually_reproducing = other._is_asexually_reproducing;
        _is_sexually_reproducing = other._is_sexually_reproducing;
        _cell = other._cell;
        for (std::list<Behavior*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
             it != it_end; ++it)
        {
            _behaviors.push_front(new Behavior(*it));
        }
        for (std::list<Sense*>::iterator it = _senses.begin(), it_end = _senses.end();
             it != it_end; ++it)
        {
            _senses.push_front(new Sense(*it));
        }
    }
    return *this;
}

bool GeneticsWorld::CreatureTracker::is_asexually_reproducing()
{
    return _is_asexually_reproducing;
}

bool GeneticsWorld::CreatureTracker::is_sexually_reproducing()
{
    return _is_sexually_reproducing;
}

void GeneticsWorld::CreatureTracker::time_step()
{
    _behaviors_used = 0;
    _senses_used = 0;
}

short GeneticsWorld::CreatureTracker::get_cell() const
{
    return _cell;
}

#endif // GW_CREATURE_TRACKER
