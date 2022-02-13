#ifndef ICYCLE_SETTER_HPP
#define ICYCLE_SETTER_HPP

#include "../observers/Observable.hpp"

class ICycleSetter : public Observable {
public:
    virtual void set_general_count(int) = 0;
    virtual void set_working_timer(int, int, int) = 0;
    virtual void set_relax_timer(int, int, int) = 0;
};

#endif