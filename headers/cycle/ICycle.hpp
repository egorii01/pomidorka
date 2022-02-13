#ifndef ICYCLE_HPP
#define ICYCLE_HPP

#include "ICycleState.hpp"

class ICycle : public ICycleState {
public:
    virtual void start_cycle() = 0;
    virtual void stop_cycle() = 0;
    virtual void pause_cycle() = 0;
    virtual void resume_cycle() = 0;

    virtual ICycle* clone() = 0;
};

#endif