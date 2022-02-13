#include "../../headers/cycle/Cycle.hpp"

Cycle::Cycle() : ObservableCycle() {
    state = DISABLE;
    init_timer();
    works_time.set_time(0, 25, 0);
    relax_time.set_time(0, 5, 0);
    timer -> registerObserver(this);
}

Cycle::Cycle(const Cycle& src) : ObservableCycle(src) {
    this -> state = src.state;
    this -> works_time = src.works_time;
    this -> relax_time = src.relax_time;

    this -> timer = src.timer -> clone();
    timer -> registerObserver(this);
}

Cycle::~Cycle() {
    delete timer;
}

void Cycle::start_cycle() {
    std::lock_guard<mutex> lock(monitor);

    state = WORKING;
    current_left_time = works_time;
    timer -> set_time(works_time.get_hours(), works_time.get_minutes(), 
        works_time.get_seconds());
    timer -> start_timer();
}

void Cycle::stop_cycle() {
    monitor.lock();
    state = DISABLE;
    timer -> stop_timer();
    current_left_time = works_time;
    monitor.unlock();

    notifyObservers(CYCLE_STOPPED);
}

void Cycle::pause_cycle() {
    state = PAUSED;
}

void Cycle::resume_cycle() {
    monitor.lock();
    if (state == PAUSED) {
        state = RELAX;
        current_left_time = relax_time;
        timer -> set_time(relax_time.get_hours(), relax_time.get_minutes(),
        relax_time.get_seconds());
        timer -> start_timer();
        monitor.unlock();
    }
    else {
        monitor.unlock();
        throw std::logic_error("Cycle is not paused");
    }
}

CycleState Cycle::get_cycle_state() {
    std::lock_guard<mutex> lock(monitor);
    return state;
}

std::string Cycle::get_left_time() {
    std::lock_guard<mutex> lock(monitor);
    return current_left_time.get_time();
}

void Cycle::set_working_timer(int hours, int minutes, int seconds) {
    std::lock_guard<mutex> lock(monitor);
    works_time.set_time(hours, minutes, seconds);
    current_left_time.set_time(hours, minutes, seconds);
}

void Cycle::set_relax_timer(int hours, int minutes, int seconds) {
    std::lock_guard<mutex> lock(monitor);
    relax_time.set_time(hours, minutes, seconds);
}

void Cycle::notification(Notification message) {
    switch (message) {
        case TIME_IS_UP:
        {
            monitor.lock();
            if (state == WORKING) {
                pause_cycle();
                monitor.unlock();

                notifyObservers(CYCLE_PAUSED);
            }
            else if (state == RELAX) {
                monitor.unlock();

                //ОПАСНОЕ МЕСТО!!! МОЖЕТ СПРОВОЦИРОВАТЬ БАГИ
                notifyObservers(CYCLE_ENDS);
                
                stop_cycle();
            }
            else {
                monitor.unlock();
            }
            break;
        }
        
        case LEFT_TIME_CHANGED:
        {
            int seconds_left = timer -> get_time_left();
        
            int minutes_left = seconds_left / 60;
            seconds_left %= 60;
        
            int hours_left = minutes_left / 60;
            minutes_left %= 60;

            monitor.lock();
            current_left_time.set_time(hours_left, minutes_left, seconds_left);
            monitor.unlock();

            break;
        }

    }

    notifyObservers(message);
}

ICycle* Cycle::clone() {
    return new Cycle(*this);
}

void Cycle::init_timer() {
    timer = new Timer;
}

Cycle::Time::Time() {
    set_time(0, 25, 0);
}

Cycle::Time::Time(int hours, int minutes, int seconds) {
    set_time(hours, minutes, seconds);
}

Cycle::Time::Time(const Cycle::Time& src) {
    set_time(src.hours, src.minutes, src.seconds);
}

Cycle::Time::~Time() {

}

void Cycle::Time::set_time(int hours, int minutes, int seconds) {
    this -> hours = hours;
    this -> minutes = minutes;
    this -> seconds = seconds;
}

std::string Cycle::Time::get_time() {
    std::string result = to_string_with_unsign_null(hours);
    result += ":";
    result += to_string_with_unsign_null(minutes);
    result += ":";
    result += to_string_with_unsign_null(seconds);

    return result;
}

std::string Cycle::Time::to_string_with_unsign_null(int value) {
    std::string result = std::to_string(value);

    if (value < 10) {
        result = "0" + result;
    }

    return result;
}

Cycle::Time& Cycle::Time::operator=(const Cycle::Time& src) {
    this -> set_time(src.hours, src.minutes, src.seconds);
    return *this;
}

int Cycle::Time::get_hours() {
    return hours;
}

int Cycle::Time::get_minutes() {
    return minutes;
}

int Cycle::Time::get_seconds() {
    return seconds;
}