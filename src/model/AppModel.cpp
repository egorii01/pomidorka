#include "../../headers/model/AppModel.hpp"

AppModel* AppModel::instance = nullptr;
std::mutex AppModel::monitor;

AppModel::AppModel() {
    cycle_link = new CycleCounter;
    configManager = new ConfigManager;
    cycle_link -> registerObserver(this);

    SettingsData config = configManager -> load_config();
    cycle_link -> set_general_count(config.cyclesCount);
    cycle_link -> set_working_timer(config.worksHours, config.worksMinutes, config.worksSeconds);
    cycle_link -> set_relax_timer(config.relaxHours, config.relaxMinutes, config.relaxSeconds);
}

AppModel::~AppModel() {
    delete cycle_link;
}

AppModel* AppModel::get_instance() {
    std::lock_guard<std::mutex> lock(AppModel::monitor);

    if (instance == nullptr) {
        instance = new AppModel;
    }
    
    return instance;
}

void AppModel::registerObserver(Observer* observer) {
    std::lock_guard<std::mutex> lock(AppModel::monitor);

    list_of_observers.push_back(observer);
}

void AppModel::removeObserver(Observer* observer) {
    std::lock_guard<std::mutex> lock(AppModel::monitor);

    list_of_observers.remove(observer);
}

void AppModel::notifyObservers(Notification message) {
    for (Observer* observer : list_of_observers) {
        observer -> notification(message);
    }
}

void AppModel::notification(Notification message) {
    std::lock_guard<std::mutex> lock(monitor);
    queue_of_notifications.push(message);
}

void AppModel::set_working_timer(int hours, int minutes, int seconds) {
    cycle_link -> set_working_timer(hours, minutes, seconds);
}

void AppModel::set_relax_timer(int hours, int minutes, int seconds) {
    cycle_link -> set_relax_timer(hours, minutes, seconds);
}

void AppModel::set_cycles_count(int value) {
    cycle_link -> set_general_count(value);
}

void AppModel::start_countdown() {
    cycle_link -> start_counter();
}

void AppModel::stop_countdown() {
    cycle_link -> stop_counter();
}

void AppModel::continue_countdown() {
    cycle_link -> continue_countdown();
}

std::string AppModel::get_cycle_state() {
    return cycle_link -> get_cycle_state();
}

std::string AppModel::get_left_time() {
    return cycle_link -> get_left_time();
}

int AppModel::get_current_number() {
    return cycle_link -> get_current_number();
}

int AppModel::get_general_cycles_count() {
    return cycle_link -> get_general_count();
}

SettingsData AppModel::get_config() {
    std::lock_guard<std::mutex> lock(monitor);
    return configManager -> load_config();
}

void AppModel::save_config(SettingsData config) {
    monitor.lock();
    configManager -> save_config(config);
    cycle_link -> set_general_count(config.cyclesCount);
    cycle_link -> set_working_timer(config.worksHours, config.worksMinutes, config.worksSeconds);
    cycle_link -> set_relax_timer(config.relaxHours, config.relaxMinutes, config.relaxSeconds);

    queue_of_notifications.push(CONFIG_CHANGED);
    monitor.unlock();
}

Notification AppModel::get_notification() {
    Notification notification;

    monitor.lock();
    if (queue_of_notifications.empty()) {
        notification = EMPTY_NOTIFICATION;
    }
    else {
        notification = queue_of_notifications.front();
        queue_of_notifications.pop();
    }
    monitor.unlock();

    return notification;
}