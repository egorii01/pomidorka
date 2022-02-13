#ifndef ICYCLE_STATE_HPP
#define ICYCLE_STATE_HPP

#include "../observers/Observable.hpp"
#include "CycleState.hpp"
#include <string>

class ICycleState : public Observable {
public:
    virtual CycleState get_cycle_state() = 0;
    virtual std::string get_left_time() = 0;
    virtual void set_working_timer(int, int, int) = 0;
    virtual void set_relax_timer(int, int, int) = 0;
};

#endif