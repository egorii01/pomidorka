#ifndef OBSERVABLE_TIMER_HPP
#define OBSERVABLE_TIMER_HPP

#include "ITimer.hpp"
#include <list>

class ObservableTimer : public ITimer {
public:

    ObservableTimer();
    ObservableTimer(const ObservableTimer&);

    virtual ~ObservableTimer();

    virtual void registerObserver(Observer*);
    virtual void removeObserver(Observer*);
    virtual void notifyObservers(Notification);
protected:
    std::list<Observer*> list_of_observers;
};

#endif