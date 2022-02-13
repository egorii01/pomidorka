#ifndef TIMER_HPP
#define TIMER_HPP

#include "ObservableTimer.hpp"

#include <thread>
#include <mutex>

using std::thread;
using std::mutex;

class Timer : public ObservableTimer {
public:
    Timer();
    Timer(int, int, int);
    Timer(const Timer&);
    virtual ~Timer();

    virtual void start_timer();
    virtual void stop_timer();
    virtual void set_time(int, int, int);
    virtual int get_time_left();
    virtual bool is_works();

    virtual ITimer* clone();

private:

    void duty_cycle();

    thread timer_thread;
    bool timer_works;

    int countdown_time;
    int seconds_left;
    mutex monitor;
};

#endif