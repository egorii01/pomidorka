#include "../../headers/timer/ObservableTimer.hpp"

ObservableTimer::ObservableTimer() {

}

ObservableTimer::ObservableTimer(const ObservableTimer& src) {
    this -> list_of_observers = src.list_of_observers;
}

ObservableTimer::~ObservableTimer() {

}

void ObservableTimer::registerObserver(Observer* observer) {
    list_of_observers.push_back(observer);
}

void ObservableTimer::removeObserver(Observer* observer) {
    list_of_observers.remove(observer);
}

void ObservableTimer::notifyObservers(Notification message) {
    for(Observer* observer : list_of_observers) {
        observer -> notification(message);
    }
}