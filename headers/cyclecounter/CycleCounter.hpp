#ifndef CYCLE_COUNTER_HPP
#define CYCLE_COUNTER_HPP

#include "ICounter.hpp"
#include "../cycle/ICycle.hpp"
#include <mutex>
#include <list>

#include "../cycle/Cycle.hpp"

class CycleCounter : public ICounter, Observer {
public:
    CycleCounter();
    CycleCounter(const CycleCounter&);

    virtual ~CycleCounter();

    virtual std::string get_left_time();
    virtual std::string get_cycle_state();
    virtual int get_general_count();
    virtual int get_current_number();

    virtual void set_general_count(int);
    virtual void set_working_timer(int, int, int);
    virtual void set_relax_timer(int, int, int);

    virtual void start_counter();
    virtual void stop_counter();
    virtual void continue_countdown();

    virtual void registerObserver(Observer*);
    virtual void removeObserver(Observer*);
    virtual void notifyObservers(Notification);

    virtual void notification(Notification);

    virtual ICounter* clone();

private:

    std::mutex monitor;

    void init_cycle();

    int general_cycle_count;
    int current_cycle_number;
    ICycle* current_cycle;

    std::list<Observer*> list_of_observers;
};

#endif