#include "../../headers/timer/Timer.hpp"

#include <iostream>
#include <exception>
#include <thread>

using namespace std;

Timer::Timer() : ObservableTimer() {
    timer_works = false;
    countdown_time = 60;
    seconds_left = countdown_time;
    timer_thread = thread(&Timer::duty_cycle, this);
    timer_thread.detach();
}

Timer::Timer(int hours, int minutes, int seconds) : ObservableTimer() {
    timer_works = false;
    countdown_time = hours * 3600 + minutes * 60 + seconds;
    seconds_left = countdown_time;
    timer_thread = thread(&Timer::duty_cycle, this);
    timer_thread.detach();
}

Timer::Timer(const Timer& src) : ObservableTimer(src) {
    this -> timer_works = src.timer_works;
    this -> countdown_time = src.countdown_time;
    this -> seconds_left = src.seconds_left;
    timer_thread = thread(&Timer::duty_cycle, this);
    timer_thread.detach();
}

Timer::~Timer() {
    
}

void Timer::start_timer() {
    if (timer_works) {
        throw logic_error("Timer is already started");
    }
    else {
        monitor.lock(); 
        seconds_left = countdown_time;
        timer_works = true;
        monitor.unlock();
    }
}

void Timer::stop_timer() {
    lock_guard<mutex> guard(monitor);
    timer_works = false;
}

void Timer::set_time(int hours, int minutes, int seconds) {
    stop_timer();
    lock_guard<mutex> guard(monitor);
    countdown_time = hours * 3600 + minutes * 60 + seconds;
}

int Timer::get_time_left() {
    lock_guard<mutex> guard(monitor);
    return seconds_left;
}

void Timer::duty_cycle() {
    while (true) {
        if (timer_works) {
            monitor.lock();
            seconds_left--;
            monitor.unlock();

            notifyObservers(LEFT_TIME_CHANGED);

            if (seconds_left == 0) {
                stop_timer();
                notifyObservers(TIME_IS_UP);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

bool Timer::is_works() {
    lock_guard<mutex> guard(monitor);
    return timer_works;
}

ITimer* Timer::clone() {
    return new Timer(*this);
}