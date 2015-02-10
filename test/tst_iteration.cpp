#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../statemachine.hpp"

#include <map>

using namespace fsm11;

using StateMachine_t = fsm11::StateMachine<>;
using State_t = StateMachine_t::state_type;

namespace
{

bool contains(const std::map<const State_t*, int>& set, State_t* state)
{
    return set.find(state) != set.end();
}

} // anonymous namespace

TEST_CASE("iterate over a single state", "[iteration]")
{
    State_t s("s");
    const State_t& cs = s;

    // The iteration starts with the state itself. A begin()-iterator is
    // never equal to an end()-iterator. If the begin()-iterator is advanced,
    // we have to reach the end()-iterator.

    SECTION("pre-order iterator")
    {
        REQUIRE(s.pre_order_begin()   != s.pre_order_end());
        REQUIRE(s.pre_order_cbegin()  != s.pre_order_cend());
        REQUIRE(cs.pre_order_begin()  != cs.pre_order_end());
        REQUIRE(cs.pre_order_cbegin() != cs.pre_order_cend());

        REQUIRE(++s.pre_order_begin()   == s.pre_order_end());
        REQUIRE(++s.pre_order_cbegin()  == s.pre_order_cend());
        REQUIRE(++cs.pre_order_begin()  == cs.pre_order_end());
        REQUIRE(++cs.pre_order_cbegin() == cs.pre_order_cend());

        REQUIRE(&s == &*s.pre_order_begin());
        REQUIRE(&s == &*s.pre_order_cbegin());
        REQUIRE(&s == &*cs.pre_order_begin());
        REQUIRE(&s == &*cs.pre_order_cbegin());
    }

    SECTION("post-order iterator")
    {
        REQUIRE(s.post_order_begin()   != s.post_order_end());
        REQUIRE(s.post_order_cbegin()  != s.post_order_cend());
        REQUIRE(cs.post_order_begin()  != cs.post_order_end());
        REQUIRE(cs.post_order_cbegin() != cs.post_order_cend());

        REQUIRE(++s.post_order_begin()   == s.post_order_end());
        REQUIRE(++s.post_order_cbegin()  == s.post_order_cend());
        REQUIRE(++cs.post_order_begin()  == cs.post_order_end());
        REQUIRE(++cs.post_order_cbegin() == cs.post_order_cend());

        REQUIRE(&s == &*s.post_order_begin());
        REQUIRE(&s == &*s.post_order_cbegin());
        REQUIRE(&s == &*cs.post_order_begin());
        REQUIRE(&s == &*cs.post_order_cbegin());
    }
}

TEST_CASE("iterate over state hierarchy", "[iteration]")
{
    State_t p("p");
    State_t c1("c1", &p);
    State_t c2("c2", &p);
    State_t c3("c3", &p);
    State_t c11("c11", &c1);
    State_t c12("c12", &c1);
    State_t c31("c31", &c3);
    State_t c32("c32", &c3);

    const State_t& cp = p;
    const State_t& cc1 = c1;

    std::vector<const State_t*> visited;

    SECTION("pre-order iterator")
    {
        SECTION("mutable iterator from pre_order_begin()/pre_order_end()")
        {
            for (auto iter = p.pre_order_begin(); iter != p.pre_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from pre_order_begin()/pre_order_end()")
        {
            for (auto iter = cp.pre_order_begin(); iter != cp.pre_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from pre_order_cbegin()/pre_order_cend()")
        {
            for (auto iter = p.pre_order_cbegin(); iter != p.pre_order_cend();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("iteration via mutable pre-order-view")
        {
            for (State_t& state : p.pre_order_subtree())
                visited.push_back(&state);
        }

        SECTION("iteration via const pre-order-view")
        {
            for (const State_t& state : cp.pre_order_subtree())
                visited.push_back(&state);
        }

        REQUIRE(visited.size() == 8);

        auto visited_iter = visited.begin();
        for (const State_t* iter : {&p, &c1, &c11, &c12, &c2, &c3, &c31, &c32})
        {
            REQUIRE(*visited_iter == iter);
            ++visited_iter;
        }
    }

    SECTION("pre-order iterator over sub-tree")
    {
        SECTION("mutable iterator from pre_order_begin()/pre_order_end()")
        {
            for (auto iter = c1.pre_order_begin(); iter != c1.pre_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from pre_order_begin()/pre_order_end()")
        {
            for (auto iter = cc1.pre_order_begin(); iter != cc1.pre_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from pre_order_cbegin()/pre_order_cend()")
        {
            for (auto iter = c1.pre_order_cbegin(); iter != c1.pre_order_cend();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("iteration via mutable pre-order-view")
        {
            for (State_t& state : c1.pre_order_subtree())
                visited.push_back(&state);
        }

        SECTION("iteration via const pre-order-view")
        {
            for (const State_t& state : cc1.pre_order_subtree())
                visited.push_back(&state);
        }

        REQUIRE(visited.size() == 3);

        auto visited_iter = visited.begin();
        for (const State_t* iter : {&c1, &c11, &c12})
        {
            REQUIRE(*visited_iter == iter);
            ++visited_iter;
        }
    }

    SECTION("post-order iterator")
    {
        SECTION("mutable iterator from post_order_begin()/post_order_end()")
        {
            for (auto iter = p.post_order_begin(); iter != p.post_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from post_order_begin()/post_order_end()")
        {
            for (auto iter = cp.post_order_begin(); iter != cp.post_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from post_order_cbegin()/post_order_cend()")
        {
            for (auto iter = p.post_order_cbegin(); iter != p.post_order_cend();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("iteration via mutable post-order-view")
        {
            for (State_t& state : p.post_order_subtree())
                visited.push_back(&state);
        }

        SECTION("iteration via const post-order-view")
        {
            for (const State_t& state : cp.post_order_subtree())
                visited.push_back(&state);
        }

        REQUIRE(visited.size() == 8);

        auto visited_iter = visited.begin();
        for (const State_t* iter : {&c11, &c12, &c1, &c2, &c31, &c32, &c3, &p})
        {
            REQUIRE(*visited_iter == iter);
            ++visited_iter;
        }
    }

    SECTION("post-order iterator over sub-tree")
    {
        SECTION("mutable iterator from post_order_begin()/post_order_end()")
        {
            for (auto iter = c1.post_order_begin(); iter != c1.post_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from post_order_begin()/post_order_end()")
        {
            for (auto iter = cc1.post_order_begin(); iter != cc1.post_order_end();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("const-iterator from post_order_cbegin()/post_order_cend()")
        {
            for (auto iter = c1.post_order_cbegin(); iter != c1.post_order_cend();
                 ++iter)
            {
                visited.push_back(&*iter);
            }
        }

        SECTION("iteration via mutable post-order-view")
        {
            for (State_t& state : c1.post_order_subtree())
                visited.push_back(&state);
        }

        SECTION("iteration via const post-order-view")
        {
            for (const State_t& state : cc1.post_order_subtree())
                visited.push_back(&state);
        }

        REQUIRE(visited.size() == 3);

        auto visited_iter = visited.begin();
        for (const State_t* iter : {&c11, &c12, &c1})
        {
            REQUIRE(*visited_iter == iter);
            ++visited_iter;
        }
    }
}

TEST_CASE("iterate over empty state machine", "[iteration]")
{
    StateMachine_t sm;
    const StateMachine_t& csm = sm;

    // There is always the root state in the state machine. A begin()-iterator
    // can never be an end()-iterator. If the begin()-iterator is advanced,
    // we have to reach the end()-iterator.

    SECTION("pre-order iterator")
    {
        REQUIRE(sm.begin()   != sm.end());
        REQUIRE(sm.cbegin()  != sm.cend());
        REQUIRE(csm.begin()  != csm.end());
        REQUIRE(csm.cbegin() != csm.cend());

        REQUIRE(++sm.begin()   == sm.end());
        REQUIRE(++sm.cbegin()  == sm.cend());
        REQUIRE(++csm.begin()  == csm.end());
        REQUIRE(++csm.cbegin() == csm.cend());
    }

    SECTION("post-order iterator")
    {
        REQUIRE(sm.post_order_begin()   != sm.post_order_end());
        REQUIRE(sm.post_order_cbegin()  != sm.post_order_cend());
        REQUIRE(csm.post_order_begin()  != csm.post_order_end());
        REQUIRE(csm.post_order_cbegin() != csm.post_order_cend());

        REQUIRE(++sm.post_order_begin()   == sm.post_order_end());
        REQUIRE(++sm.post_order_cbegin()  == sm.post_order_cend());
        REQUIRE(++csm.post_order_begin()  == csm.post_order_end());
        REQUIRE(++csm.post_order_cbegin() == csm.post_order_cend());
    }

//    SECTION("atomic iterator")
//    {
//        REQUIRE(sm.atomic_begin()   != sm.atomic_end());
//        REQUIRE(sm.atomic_cbegin()  != sm.atomic_cend());
//        REQUIRE(csm.atomic_begin()  != csm.atomic_end());
//        REQUIRE(csm.atomic_cbegin() != csm.atomic_cend());

//        REQUIRE(++sm.atomic_begin()   == sm.atomic_end());
//        REQUIRE(++sm.atomic_cbegin()  == sm.atomic_cend());
//        REQUIRE(++csm.atomic_begin()  == csm.atomic_end());
//        REQUIRE(++csm.atomic_cbegin() == csm.atomic_cend());
//    }
}

TEST_CASE("iterate over non-empty state machine", "[iteration]")
{
    StateMachine_t sm;
    const StateMachine_t& csm = sm;
    State_t p("p", &sm);
    State_t c1("c1", &p);
    State_t c2("c2", &p);
    State_t c3("c3", &p);
    State_t c11("c11", &c1);
    State_t c12("c12", &c1);
    State_t c31("c31", &c3);
    State_t c32("c32", &c3);
    c3.setChildMode(State_t::ChildMode::Parallel);

    std::map<const State_t*, int> visitOrder;
    int counter = 0;

    SECTION("pre-order iterator")
    {
        SECTION("mutable iterator from begin()/end()")
        {
            for (StateMachine_t::pre_order_iterator iter = sm.begin();
                 iter != sm.end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from begin()/end()")
        {
            for (StateMachine_t::const_pre_order_iterator iter = csm.begin();
                 iter != csm.end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from cbegin()/cend()")
        {
            for (StateMachine_t::const_pre_order_iterator iter = sm.cbegin();
                 iter != sm.cend(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        REQUIRE(counter == 9);

        // Parents have to be visited before their children.
        REQUIRE(visitOrder[&p] < visitOrder[&c1]);
        REQUIRE(visitOrder[&p] < visitOrder[&c2]);
        REQUIRE(visitOrder[&p] < visitOrder[&c3]);
        REQUIRE(visitOrder[&c1] < visitOrder[&c11]);
        REQUIRE(visitOrder[&c1] < visitOrder[&c12]);
        REQUIRE(visitOrder[&c3] < visitOrder[&c31]);
        REQUIRE(visitOrder[&c3] < visitOrder[&c32]);
    }

    SECTION("pre-order iterator with child skipping")
    {
        StateMachine_t::pre_order_iterator iter = sm.begin();
        ++iter;
        ++iter;
        REQUIRE(&*iter == &c1);

        iter.skipChildren();
        while (iter != sm.end())
        {
            visitOrder[&*iter] = ++counter;
            ++iter;
        }

        REQUIRE(counter == 5);
        REQUIRE(contains(visitOrder, &c1));
        REQUIRE(contains(visitOrder, &c2));
        REQUIRE(contains(visitOrder, &c3));
        REQUIRE(contains(visitOrder, &c31));
        REQUIRE(contains(visitOrder, &c32));

        REQUIRE(!contains(visitOrder, &c11));
        REQUIRE(!contains(visitOrder, &c12));
    }

    SECTION("post-order iterator")
    {
        SECTION("mutable iterator from begin()/end()")
        {
            for (StateMachine_t::post_order_iterator iter = sm.post_order_begin();
                 iter != sm.post_order_end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from begin()/end()")
        {
            for (StateMachine_t::const_post_order_iterator iter
                     = csm.post_order_begin();
                 iter != csm.post_order_end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from cbegin()/cend()")
        {
            for (StateMachine_t::const_post_order_iterator iter
                     = sm.post_order_cbegin();
                 iter != sm.post_order_cend(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        REQUIRE(counter == 9);

        // Parents have to be visited after their children.
        REQUIRE(visitOrder[&p] > visitOrder[&c1]);
        REQUIRE(visitOrder[&p] > visitOrder[&c2]);
        REQUIRE(visitOrder[&p] > visitOrder[&c3]);
        REQUIRE(visitOrder[&c1] > visitOrder[&c11]);
        REQUIRE(visitOrder[&c1] > visitOrder[&c12]);
        REQUIRE(visitOrder[&c3] > visitOrder[&c31]);
        REQUIRE(visitOrder[&c3] > visitOrder[&c32]);
    }

#if 0
    SECTION("atomic iterator")
    {
        SECTION("mutable iterator from begin()/end()")
        {
            for (StateMachine_t::atomic_iterator iter = sm.atomic_begin();
                 iter != sm.atomic_end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from begin()/end()")
        {
            for (StateMachine_t::const_atomic_iterator iter = csm.atomic_begin();
                 iter != csm.atomic_end(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        SECTION("const-iterator from cbegin()/cend()")
        {
            for (StateMachine_t::const_atomic_iterator iter = sm.atomic_cbegin();
                 iter != sm.atomic_cend(); ++iter)
            {
                visitOrder[&*iter] = ++counter;
            }
        }

        REQUIRE(counter == 5);

        REQUIRE(contains(visitOrder, &c2));
        REQUIRE(contains(visitOrder, &c11));
        REQUIRE(contains(visitOrder, &c12));
        REQUIRE(contains(visitOrder, &c31));
        REQUIRE(contains(visitOrder, &c32));
    }
#endif

    SECTION("works with <algorithm>")
    {
        auto predicate = [](const State_t&) { return true; };
        REQUIRE(std::count_if(sm.begin(),   sm.end(),
                              predicate) == 9);
        REQUIRE(std::count_if(sm.cbegin(),  sm.cend(),
                              predicate) == 9);
        REQUIRE(std::count_if(csm.begin(),  csm.end(),
                              predicate) == 9);
        REQUIRE(std::count_if(csm.cbegin(), csm.cend(),
                              predicate) == 9);

        REQUIRE(std::count_if(sm.post_order_begin(), sm.post_order_end(),
                              predicate) == 9);
        REQUIRE(std::count_if(csm.post_order_begin(), csm.post_order_end(),
                              predicate) == 9);
        REQUIRE(std::count_if(sm.post_order_cbegin(), sm.post_order_cend(),
                              predicate) == 9);
        REQUIRE(std::count_if(csm.post_order_cbegin(), csm.post_order_cend(),
                              predicate) == 9);

//        REQUIRE(std::count_if(sm.atomic_begin(), sm.atomic_end(),
//                              predicate) == 5);
//        REQUIRE(std::count_if(csm.atomic_begin(), csm.atomic_end(),
//                              predicate) == 5);
//        REQUIRE(std::count_if(sm.atomic_cbegin(), sm.atomic_cend(),
//                              predicate) == 5);
//        REQUIRE(std::count_if(csm.atomic_cbegin(), csm.atomic_cend(),
//                              predicate) == 5);
    }
}

TEST_CASE("start empty fsm", "[start]")
{
    StateMachine_t sm;

    REQUIRE(sm.running() == false);
    sm.start();
    REQUIRE(sm.running() == true);
    sm.stop();
    REQUIRE(sm.running() == false);
    sm.start();
    REQUIRE(sm.running() == true);
    sm.stop();
    REQUIRE(sm.running() == false);
}

TEST_CASE("restart empty fsm", "[start]")
{
    StateMachine_t sm;

    REQUIRE(sm.running() == false);
    sm.start();
    REQUIRE(sm.running() == true);
    sm.start();
    REQUIRE(sm.running() == true);
    sm.stop();
    REQUIRE(sm.running() == false);
    sm.stop();
    REQUIRE(sm.running() == false);
}

TEST_CASE("start fsm with compound state", "[start]")
{
    StateMachine_t sm;

    State_t a("a", &sm);
    State_t b("b", &sm);
    State_t c("c", &sm);

    REQUIRE(sm.running() == false);
    REQUIRE(sm.isActive() == false);

    sm.start();
    REQUIRE(sm.running() == true);

    sm.stop();
    REQUIRE(sm.running() == false);
}