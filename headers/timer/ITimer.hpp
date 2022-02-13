#ifndef ITIMER_HPP
#define ITIMER_HPP

#include "../observers/Observable.hpp"

class ITimer : public Observable {
public:
    virtual void start_timer() = 0;
    virtual void stop_timer() = 0;
    virtual void set_time(int, int, int) = 0;
    virtual int get_time_left() = 0;
    virtual bool is_works() = 0;

    virtual ITimer* clone() = 0;
};

#endif