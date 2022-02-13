#include "../../headers/cyclecounter/CycleCounter.hpp"

CycleCounter::CycleCounter() {
    general_cycle_count = 10;
    current_cycle_number = 0;
    init_cycle();
    current_cycle -> registerObserver(this);
}

CycleCounter::CycleCounter(const CycleCounter& src) {
    this -> general_cycle_count = src.general_cycle_count;
    this -> current_cycle_number = src.current_cycle_number;
    this -> current_cycle = src.current_cycle -> clone();

    current_cycle -> registerObserver(this);
}

CycleCounter::~CycleCounter() {
    delete current_cycle;
}

void CycleCounter::init_cycle() {
    current_cycle = new Cycle;
}

std::string CycleCounter::get_left_time() {
    return current_cycle -> get_left_time();
}

std::string CycleCounter::get_cycle_state() {
    CycleState state = current_cycle -> get_cycle_state();

    if (state == WORKING) {
        return "Working";
    }
    else if (state == RELAX) {
        return "Relax";
    }
    else if (state == PAUSED) {
        return "Paused";
    }
    else {
        return "Disabled";
    }
}

int CycleCounter::get_general_count() {
    std::lock_guard<std::mutex> lock(monitor);
    return general_cycle_count;
}

int CycleCounter::get_current_number() {
    std::lock_guard<std::mutex> lock(monitor);
    return current_cycle_number;
}

void CycleCounter::set_general_count(int count) {
    std::lock_guard<std::mutex> lock(monitor);
    general_cycle_count = count;
}

void CycleCounter::set_working_timer(int hours, int minutes, int seconds) {
    current_cycle -> set_working_timer(hours, minutes, seconds);
}

void CycleCounter::set_relax_timer(int hours, int minutes, int seconds) {
    current_cycle -> set_relax_timer(hours, minutes, seconds);
}

void CycleCounter::start_counter() {
    monitor.lock();
    current_cycle_number = 1;
    monitor.unlock();

    current_cycle -> start_cycle();
}

void CycleCounter::stop_counter() {
    monitor.lock();
    current_cycle_number = 0;
    monitor.unlock();
    current_cycle -> stop_cycle();
    notifyObservers(COUNTDOWN_STOPPED);
}

/*при каждой приостановке цикла планируется вывод диалогового окна
данный метод необходим для продолжения отсчета после приема соответствующей команды*/
void CycleCounter::continue_countdown() {
    if (current_cycle -> get_cycle_state() == DISABLE) {

        current_cycle -> start_cycle();
    
    }
    else if (current_cycle -> get_cycle_state() == PAUSED) {
        
        try {
            current_cycle -> resume_cycle();
        }
        catch (std::exception) {
            
        }

    }
}

void CycleCounter::registerObserver(Observer* observer) {
    list_of_observers.push_back(observer);
}

void CycleCounter::removeObserver(Observer* observer) {
    list_of_observers.remove(observer);
}

void CycleCounter::notifyObservers(Notification message) {
    for (Observer* observer : list_of_observers) {
        observer -> notification(message);
    }
}

void CycleCounter::notification(Notification message) {
    bool is_last_cycle = false;
    
    switch (message) {
        case CYCLE_ENDS:
        {
            monitor.lock();
            if (current_cycle_number < general_cycle_count) {
                current_cycle_number++;
                monitor.unlock();
            }
            else {
                monitor.unlock();
                is_last_cycle = true;
                notifyObservers(COUNTDOWN_ENDS);
            }
            break;
        }
    }

    /*условие для подмены уведомления CYCLE_ENDS на COUNTDOWN_ENDS
    при необходимости*/
    if (message != CYCLE_ENDS || !is_last_cycle) {
        notifyObservers(message);
    }
}

ICounter* CycleCounter::clone() {
    return new CycleCounter(*this);
}