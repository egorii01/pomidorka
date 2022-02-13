#ifndef CYCLE_HPP
#define CYCLE_HPP

#include <mutex>
#include "../timer/ITimer.hpp"
#include "ObservableCycle.hpp"
#include "../observers/Observer.hpp"

#include "../timer/Timer.hpp"

class Cycle : public ObservableCycle, Observer {
public:

    Cycle();
    Cycle(const Cycle&);

    virtual ~Cycle();

    virtual void start_cycle();
    virtual void stop_cycle();
    virtual void pause_cycle();
    virtual void resume_cycle();

    virtual CycleState get_cycle_state();
    virtual std::string get_left_time();
    virtual void set_working_timer(int, int, int);
    virtual void set_relax_timer(int, int, int);

    virtual void notification(Notification);
    virtual ICycle* clone();

private:

    void init_timer();

    class Time {
    public:
        Time();
        Time(int, int, int);
        Time(const Time&);
        ~Time();

        void set_time(int, int, int);
        std::string get_time();

        int get_hours();
        int get_minutes();
        int get_seconds();

        Time& operator=(const Time&);

    private:

        std::string to_string_with_unsign_null(int);
        int hours;
        int minutes;
        int seconds;
    };

    //мьютекс для потокобезопасности
    std::mutex monitor;

    //оставшееся время до конца части цикла
    Time current_left_time;

    Time works_time;
    Time relax_time;
    CycleState state;
    ITimer* timer;

};

#endif