#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Notification.hpp"

class Observer {
public:
    virtual void notification(Notification) = 0;
};

#endif