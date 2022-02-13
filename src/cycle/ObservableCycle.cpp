#include "../../headers/cycle/ObservableCycle.hpp"

ObservableCycle::ObservableCycle() {

}

ObservableCycle::ObservableCycle(const ObservableCycle& src) {
    this -> list_of_observers = src.list_of_observers;
}

ObservableCycle::~ObservableCycle() {

}

void ObservableCycle::registerObserver(Observer* observer) {
    list_of_observers.push_back(observer);
}

void ObservableCycle::removeObserver(Observer* observer) {
    list_of_observers.remove(observer);
}

void ObservableCycle::notifyObservers(Notification message) {
    for(Observer* observer : list_of_observers) {
        observer -> notification(message);
    }
}