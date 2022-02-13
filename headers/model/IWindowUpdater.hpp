#ifndef IWINDOW_UPDATER
#define IWINDOW_UPDATER

#include <string>

class IWindowUpdater {
public:
    virtual std::string get_cycle_state() = 0;
    virtual std::string get_left_time() = 0;
    virtual int get_current_number() = 0;
    virtual int get_general_cycles_count() = 0;
};

#endif