#ifndef APP_MODEL_HPP
#define APP_MODEL_HPP

#include "IModel.hpp"
#include "../facade/IFacade.hpp"
#include "../cyclecounter/ICounter.hpp"
#include "../configManager/ConfigManager.hpp"
#include "../cyclecounter/CycleCounter.hpp"
#include <mutex>
#include <list>
#include <queue>

class AppModel :
public IModel,
public Observer,
public IFacade {

public:

    AppModel(const AppModel&) = delete;
    void operator=(const AppModel&) = delete;

    static AppModel* get_instance();

    virtual void registerObserver(Observer*);
    virtual void removeObserver(Observer*);
    virtual void notifyObservers(Notification);

    virtual std::string get_cycle_state();
    virtual std::string get_left_time();
    virtual int get_current_number();
    virtual int get_general_cycles_count();

    virtual SettingsData get_config();

    virtual void notification(Notification);

    virtual void save_config(SettingsData);

    virtual void set_working_timer(int, int, int);
    virtual void set_relax_timer(int, int, int);
    virtual void set_cycles_count(int);

    virtual void start_countdown();
    virtual void stop_countdown();
    virtual void continue_countdown();

    virtual Notification get_notification();

private:
    AppModel();
    virtual ~AppModel();

private:
    static AppModel* instance;
    static std::mutex monitor;

    std::list<Observer*> list_of_observers;
    ICounter* cycle_link;
    IConfigManager* configManager;

    std::queue<Notification> queue_of_notifications;

};

#endif