#ifndef ICOUNTER_HPP
#define ICOUNTER_HPP

#include "ICycleGetter.hpp"
#include "ICycleSetter.hpp"
#include "../observers/Observable.hpp"

class ICounter : public ICycleGetter {
public:
    virtual void start_counter() = 0;
    virtual void stop_counter() = 0;
    virtual void continue_countdown() = 0;

    virtual ICounter* clone() = 0;
};

#endif