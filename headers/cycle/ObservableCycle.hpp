#ifndef OBSERVABLE_CYCLE_HPP
#define OBSERVABLE_CYCLE_HPP

#include "ICycle.hpp"
#include <list>

class ObservableCycle : public ICycle {
public:

    ObservableCycle();
    ObservableCycle(const ObservableCycle&);

    virtual ~ObservableCycle();

    virtual void registerObserver(Observer*);
    virtual void removeObserver(Observer*);
    virtual void notifyObservers(Notification);
protected:
    std::list<Observer*> list_of_observers;
};

#endif