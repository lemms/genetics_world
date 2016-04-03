// gw_creature_tracker.cpp

#include "gw_creature_tracker.h"

GeneticsWorld::CreatureTracker::BehaviorImpl::BehaviorImpl(CreatureTracker* creature_tracker,
                                                           float inheritance)
    : _creature_tracker(creature_tracker),
      _inheritance(inheritance)
{
}

GeneticsWorld::CreatureTracker::BehaviorImpl::~BehaviorImpl()
{
}

void GeneticsWorld::CreatureTracker::BehaviorImpl::set_inheritance(float inheritance)
{
    _inheritance = inheritance;
}

float GeneticsWorld::CreatureTracker::BehaviorImpl::get_inheritance() const
{
    return _inheritance;
}

GeneticsWorld::CreatureTracker::SenseImpl::SenseImpl(CreatureTracker* creature_tracker,
                                                     float inheritance)
    : _creature_tracker(creature_tracker),
      _inheritance(inheritance)
{
}

GeneticsWorld::CreatureTracker::SenseImpl::~Sense()
{
}

void GeneticsWorld::CreatureTracker::SenseImpl::set_inheritance(float inheritance)
{
}

float GeneticsWorld::CreatureTracker::SenseImpl::get_inheritance() const
{
}

GeneticsWorld::Behavior::Behavior(BehaviorImpl* impl)
    : _impl(impl)
{
}

GeneticsWorld::Behavior::~Behavior()
{
}

void GeneticsWorld::Behavior::do_behavior() const
{
    _impl->do_behavior();
}

void GeneticsWorld::Behavior::set_inheritance(float inheritance)
{
    _impl->set_inheritance(inheritance);
}

float GeneticsWorld::Behavior::get_inheritance() const
{
    return _impl->get_inheritance();
}

GeneticsWorld::Sense::Sense(SenseImpl* impl)
    : _impl(impl)
{
}

GeneticsWorld::Sense::~Sense()
{
}

float GeneticsWorld::Sense::do_sense() const
{
    return _impl->do_sense();
}

void GeneticsWorld::Sense::set_inheritance(float inheritance)
{
    _impl->set_inheritance(inheritance);
}

float GeneticsWorld::Sense::get_inheritance() const
{
    return _impl->get_inheritance();
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
    for (std::list<BehaviorImpl*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
         it != it_end; ++it)
    {
        delete *it;
    }
    for (std::list<SenseImpl*>::iterator it = _senses.begin(), it_end = _senses.end();
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
    for (std::list<BehaviorImpl*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
         it != it_end; ++it)
    {
        _behaviors.push_front(new BehaviorImpl(*it));
    }
    for (std::list<SenseImpl*>::iterator it = _senses.begin(), it_end = _senses.end();
         it != it_end; ++it)
    {
        _senses.push_front(new SenseImpl(*it));
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
        for (std::list<BehaviorImpl*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
             it != it_end; ++it)
        {
            _behaviors.push_front(new BehaviorImpl(*it));
        }
        for (std::list<SenseImpl*>::iterator it = _senses.begin(), it_end = _senses.end();
             it != it_end; ++it)
        {
            _senses.push_front(new SenseImpl(*it));
        }
    }
    return *this;
}

bool GeneticsWorld::CreatureTracker::is_asexually_reproducing() const
{
    return _is_asexually_reproducing;
}

bool GeneticsWorld::CreatureTracker::is_sexually_reproducing() const
{
    return _is_sexually_reproducing;
}

bool GeneticsWorld::CreatureTracker::is_dead() const
{
    return _energy <= 0.0f || _life_span <= 0;
}

void GeneticsWorld::CreatureTracker::time_step()
{
    _behaviors_used = 0;
    _senses_used = 0;
    _life_span--;
}

short GeneticsWorld::CreatureTracker::get_cell() const
{
    return _cell;
}
