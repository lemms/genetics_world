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

        bool is_asexually_reproducing() const;
        bool is_sexually_reproducing() const;
        bool is_dead() const;

        void time_step();

        short get_cell() const;

        class BehaviorImpl {
        public:
            BehaviorImpl(CreatureTracker* creature_tracker, float inheritance);
            virtual ~BehaviorImpl();
            virtual void do_behavior() = 0;
            void set_inheritance(float inheritance);
            float get_inheritance() const;
        protected:
            CreatureTracker* _creature_tracker;
            float _inheritance;
        };

        class SenseImpl {
        public:
            SenseImpl(const CreatureTracker* creature_tracker, float inheritance);
            virtual ~SenseImpl();
            virtual float do_sense() const = 0;
            void set_inheritance(float inheritance);
            float get_inheritance() const;
        protected:
            const CreatureTracker* _creature_tracker;
            float _inheritance;
        };

        friend class BehaviorFactory;
        friend class SenseFactory;

    private:
        short _life_span;
        mutable float _energy;
        short _behaviors_used;
        mutable short _senses_used;
        short _max_behaviors_per_time_step;
        short _max_senses_per_time_step;
        bool _is_asexually_reproducing;
        bool _is_sexually_reproducing;
        short _cell;

        std::list<BehaviorImpl*> _behaviors;
        std::list<SenseImpl*> _senses;
    };

    class Behavior {
    public:
        Behavior(BehaviorImpl* impl);
        ~Behavior();
        void do_behavior() const;
        void set_inheritance(float inheritance);
        float get_inheritance() const;
    };

    class Sense {
    public:
        Sense(SenseImpl* impl);
        ~Sense();
        float do_sense() const;
        void set_inheritance(float inheritance);
        float get_inheritance() const;
    };
}

#endif // GW_CREATURE_TRACKER
