#ifndef ISETTINGS_WINDOW_FACADE_HPP
#define ISETTINGS_WINDOW_FACADE_HPP

class ISettingsWindowFacade {
public:
    virtual void set_working_timer(int, int, int) = 0;
    virtual void set_relax_timer(int, int, int) = 0;
    virtual void set_cycles_count(int) = 0;
};

#endif