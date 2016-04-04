// gw_creature_tracker.cpp

#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
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

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_life_span()
{
    return _creature_tracker->_life_span;
}

float& GeneticsWorld::CreatureTracker::BehaviorImpl::_energy()
{
    return _creature_tracker->_energy;
}

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_behaviors_used()
{
    return _creature_tracker->_behaviors_used;
}

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_senses_used()
{
    return _creature_tracker->_senses_used;
}

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_max_behaviors_per_time_step()
{
    return _creature_tracker->_max_behaviors_per_time_step;
}

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_max_senses_per_time_step()
{
    return _creature_tracker->_max_senses_per_time_step;
}

bool& GeneticsWorld::CreatureTracker::BehaviorImpl::_is_asexually_reproducing()
{
    return _creature_tracker->_is_asexually_reproducing;
}

bool& GeneticsWorld::CreatureTracker::BehaviorImpl::_is_sexually_reproducing()
{
    return _creature_tracker->_is_sexually_reproducing;
}

short& GeneticsWorld::CreatureTracker::BehaviorImpl::_cell()
{
    return _creature_tracker->_cell;
}

GeneticsWorld::CreatureTracker::SenseImpl::SenseImpl(CreatureTracker* creature_tracker,
                                                     float inheritance)
    : _creature_tracker(creature_tracker),
      _inheritance(inheritance)
{
}

GeneticsWorld::CreatureTracker::SenseImpl::~SenseImpl()
{
}

void GeneticsWorld::CreatureTracker::SenseImpl::set_inheritance(float inheritance)
{
    _inheritance = inheritance;
}

float GeneticsWorld::CreatureTracker::SenseImpl::get_inheritance() const
{
    return _inheritance;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_life_span()
{
    return _creature_tracker->_life_span;
}

float& GeneticsWorld::CreatureTracker::SenseImpl::_energy()
{
    return _creature_tracker->_energy;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_behaviors_used()
{
    return _creature_tracker->_behaviors_used;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_senses_used()
{
    return _creature_tracker->_senses_used;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_max_behaviors_per_time_step()
{
    return _creature_tracker->_max_behaviors_per_time_step;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_max_senses_per_time_step()
{
    return _creature_tracker->_max_senses_per_time_step;
}

bool& GeneticsWorld::CreatureTracker::SenseImpl::_is_asexually_reproducing()
{
    return _creature_tracker->_is_asexually_reproducing;
}

bool& GeneticsWorld::CreatureTracker::SenseImpl::_is_sexually_reproducing()
{
    return _creature_tracker->_is_sexually_reproducing;
}

short& GeneticsWorld::CreatureTracker::SenseImpl::_cell()
{
    return _creature_tracker->_cell;
}

GeneticsWorld::Behavior::Behavior(CreatureTracker::BehaviorImpl* impl)
    : _impl(impl)
{
}

GeneticsWorld::Behavior::~Behavior()
{
}

void GeneticsWorld::Behavior::do_behavior()
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

std::string GeneticsWorld::Behavior::get_name() const
{
    return _impl->get_name();
}

GeneticsWorld::Sense::Sense(CreatureTracker::SenseImpl* impl)
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

std::string GeneticsWorld::Sense::get_name() const
{
    return _impl->get_name();
}

template <class T>
void build_genetics(std::list<T*>& child_features,
                    short num_parent_features,
                    const std::vector<float>& parent_feature_inheritance,
                    const std::vector<typename std::list<T*>::iterator>& parent_feature)
{    
    // randomly add or subtract a feature
    short random_feature_increment = rand() % 100;
    if (random_feature_increment < 5)
    {
        num_parent_features++;
    }
    else if (random_feature_increment < 10)
    {
        num_parent_features--;
    }

    float total_influence = 0.0f;
    for (std::vector<float>::const_iterator it = parent_feature_inheritance.cbegin(), it_end = parent_feature_inheritance.cend();
         it != it_end; ++it)
    {
        total_influence += *it;
    }

    short num_randomizing_indices = 10000;
    std::vector<short> randomizing_indices(num_randomizing_indices);

    short index = 0;
    short original_index = 0;
    for (std::vector<float>::const_iterator it = parent_feature_inheritance.cbegin(), it_end = parent_feature_inheritance.cend();
         it != it_end; ++it, ++original_index)
    {
        float percentage = *it / total_influence;
        short indices = static_cast<short>(percentage * static_cast<float>(num_randomizing_indices));
        for (short i = 0; i < indices; ++i)
        {
            if (index < randomizing_indices.size())
            {
                randomizing_indices[index] = original_index;
            }
            else
            {
                break;
            }
            index++;
        }
    }

    // TODO: de-duplicate
    for (short f = 0; f < num_parent_features; ++f)
    {
        short random_index = rand() % num_randomizing_indices;
        child_features.push_front((*parent_feature[random_index])->clone());
    }

    // TODO: add a random mutation
}


GeneticsWorld::CreatureTracker::CreatureTracker(short cell,
                                                CreatureTracker* lhs_parent,
                                                CreatureTracker* rhs_parent)
    : _life_span(100),
      _energy(100.0f),
      _behaviors_used(0),
      _senses_used(0),
      _max_behaviors_per_time_step(2),
      _max_senses_per_time_step(2),
      _is_asexually_reproducing(false),
      _is_sexually_reproducing(false),
      _cell(cell)
{
    // copy parent behaviors and senses based on inheritance values
    // add random mutations
    // 1) add new behaiors/sense randomly
    // 2) modify inheritance values randomly

    if (lhs_parent != NULL)
    {
        if (rhs_parent != NULL)
        {
            // two parents
            std::vector<float> parent_behavior_inheritance;
            std::vector<std::list<BehaviorImpl*>::iterator> parent_behaviors;
            for (std::list<BehaviorImpl*>::iterator it = lhs_parent->_behaviors.begin(), it_end = lhs_parent->_behaviors.end();
                 it != it_end; ++it)
            {
                parent_behavior_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_behaviors.push_back(it);
            }
            for (std::list<BehaviorImpl*>::iterator it = rhs_parent->_behaviors.begin(), it_end = rhs_parent->_behaviors.end();
                 it != it_end; ++it)
            {
                parent_behavior_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_behaviors.push_back(it);
            }

            std::vector<float> parent_sense_inheritance;
            std::vector<std::list<SenseImpl*>::iterator> parent_senses;
            for (std::list<SenseImpl*>::iterator it = lhs_parent->_senses.begin(), it_end = lhs_parent->_senses.end();
                 it != it_end; ++it)
            {
                parent_sense_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_senses.push_back(it);
            }
            for (std::list<SenseImpl*>::iterator it = rhs_parent->_senses.begin(), it_end = rhs_parent->_senses.end();
                 it != it_end; ++it)
            {
                parent_sense_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_senses.push_back(it);
            }

            build_genetics<BehaviorImpl>(_behaviors, parent_behavior_inheritance.size() / 2, parent_behavior_inheritance, parent_behaviors);
            build_genetics<SenseImpl>(_senses, parent_sense_inheritance.size() / 2, parent_sense_inheritance, parent_senses);
        }
        else
        {
            // one parent
            std::vector<float> parent_behavior_inheritance;
            std::vector<std::list<BehaviorImpl*>::iterator> parent_behaviors;
            for (std::list<BehaviorImpl*>::iterator it = lhs_parent->_behaviors.begin(), it_end = lhs_parent->_behaviors.end();
                 it != it_end; ++it)
            {
                parent_behavior_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_behaviors.push_back(it);
            }

            std::vector<float> parent_sense_inheritance;
            std::vector<std::list<SenseImpl*>::iterator> parent_senses;
            for (std::list<SenseImpl*>::iterator it = lhs_parent->_senses.begin(), it_end = lhs_parent->_senses.end();
                 it != it_end; ++it)
            {
                parent_sense_inheritance.push_back(fabsf((*it)->get_inheritance()));
                parent_senses.push_back(it);
            }

            build_genetics<BehaviorImpl>(_behaviors, parent_behavior_inheritance.size(), parent_behavior_inheritance, parent_behaviors);
            build_genetics<SenseImpl>(_senses, parent_sense_inheritance.size(), parent_sense_inheritance, parent_senses);
        }
    }
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
    for (std::list<BehaviorImpl*>::const_iterator it = other._behaviors.begin(), it_end = other._behaviors.end();
         it != it_end; ++it)
    {
        _behaviors.push_front((*it)->clone());
    }
    for (std::list<SenseImpl*>::const_iterator it = other._senses.begin(), it_end = other._senses.end();
         it != it_end; ++it)
    {
        _senses.push_front((*it)->clone());
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
            delete *it;
        }
        for (std::list<SenseImpl*>::iterator it = _senses.begin(), it_end = _senses.end();
             it != it_end; ++it)
        {
            delete *it;
        }
        _behaviors.clear();
        _senses.clear();
        for (std::list<BehaviorImpl*>::const_iterator it = other._behaviors.cbegin(), it_end = other._behaviors.cend();
             it != it_end; ++it)
        {
            _behaviors.push_front((*it)->clone());
        }
        for (std::list<SenseImpl*>::const_iterator it = other._senses.cbegin(), it_end = other._senses.cend();
             it != it_end; ++it)
        {
            _senses.push_front((*it)->clone());
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
    _energy -= 1.0f;
    _life_span--;
}

short GeneticsWorld::CreatureTracker::get_cell() const
{
    return _cell;
}

std::list<GeneticsWorld::Behavior*> GeneticsWorld::CreatureTracker::get_behaviors()
{
    std::list<Behavior*> behaviors;
    for (std::list<BehaviorImpl*>::iterator it = _behaviors.begin(), it_end = _behaviors.end();
         it != it_end; ++it)
    {
        behaviors.push_front(new Behavior(*it));
    }
    return behaviors;
}

std::list<GeneticsWorld::Sense*> GeneticsWorld::CreatureTracker::get_senses()
{
    std::list<Sense*> senses;
    for (std::list<SenseImpl*>::iterator it = _senses.begin(), it_end = _senses.end();
         it != it_end; ++it)
    {
        senses.push_front(new Sense(*it));
    }
    return senses;
}
