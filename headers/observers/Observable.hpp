#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include "Observer.hpp"

class Observable {
public:
    virtual void registerObserver(Observer*) = 0;
    virtual void removeObserver(Observer*) = 0;
    virtual void notifyObservers(Notification) = 0;
};

#endif