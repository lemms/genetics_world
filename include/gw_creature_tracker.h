// gw_creature_tracker.h

#ifndef GW_CREATURE_TRACKER
#define GW_CREATURE_TRACKER

#include <string>
#include <list>

namespace GeneticsWorld
{
    class Behavior;
    class Sense;
    class CreatureTracker
    {
    public:
        CreatureTracker(long cell, CreatureTracker* lhs_parent, CreatureTracker* rhs_parent);
        ~CreatureTracker();
        CreatureTracker(const CreatureTracker& other);
        CreatureTracker& operator=(const CreatureTracker& other);

        bool is_asexually_reproducing() const;
        bool is_sexually_reproducing() const;
        bool is_dead() const;

        void time_step();

        long get_cell() const;

        std::list<Behavior*> get_behaviors();
        std::list<Sense*> get_senses();

        class BehaviorImpl {
        public:
            BehaviorImpl(CreatureTracker* creature_tracker, float inheritance);
            virtual ~BehaviorImpl();
            virtual void do_behavior() = 0;
            void set_inheritance(float inheritance);
            float get_inheritance() const;
            virtual std::string get_name() const = 0;
            virtual BehaviorImpl* clone() const = 0;
        protected:
            long& _life_span();
            float& _energy();
            long& _behaviors_used();
            long& _senses_used();
            long& _max_behaviors_per_time_step();
            long& _max_senses_per_time_step();
            bool& _is_asexually_reproducing();
            bool& _is_sexually_reproducing();
            long& _cell();
            CreatureTracker* _creature_tracker;
            float _inheritance;
        };

        class SenseImpl {
        public:
            SenseImpl(CreatureTracker* creature_tracker, float inheritance);
            virtual ~SenseImpl();
            virtual float do_sense() = 0;
            void set_inheritance(float inheritance);
            float get_inheritance() const;
            virtual std::string get_name() const = 0;
            virtual SenseImpl* clone() const = 0;
        protected:
            long& _life_span();
            float& _energy();
            long& _behaviors_used();
            long& _senses_used();
            long& _max_behaviors_per_time_step();
            long& _max_senses_per_time_step();
            bool& _is_asexually_reproducing();
            bool& _is_sexually_reproducing();
            long& _cell();
            CreatureTracker* _creature_tracker;
            float _inheritance;
        };

        friend class BehaviorImpl;
        friend class SenseImpl;
        friend class BehaviorFactory;
        friend class SenseFactory;

    private:
        long _life_span;
        mutable float _energy;
        long _behaviors_used;
        mutable long _senses_used;
        long _max_behaviors_per_time_step;
        long _max_senses_per_time_step;
        bool _is_asexually_reproducing;
        bool _is_sexually_reproducing;
        long _cell;

        std::list<BehaviorImpl*> _behaviors;
        std::list<SenseImpl*> _senses;
    };

    class Behavior {
    public:
        Behavior(CreatureTracker::BehaviorImpl* impl);
        ~Behavior();
        void do_behavior();
        void set_inheritance(float inheritance);
        float get_inheritance() const;
        std::string get_name() const;
    private:
        CreatureTracker::BehaviorImpl* _impl;
    };

    class Sense {
    public:
        Sense(CreatureTracker::SenseImpl* impl);
        ~Sense();
        float do_sense() const;
        void set_inheritance(float inheritance);
        float get_inheritance() const;
        std::string get_name() const;
    private:
        CreatureTracker::SenseImpl* _impl;
    };
}

#endif // GW_CREATURE_TRACKER
