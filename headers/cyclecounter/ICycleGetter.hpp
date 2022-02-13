#ifndef ICYCLE_GETTER
#define ICYCLE_GETTER

#include <string>
#include "../cycle/ICycle.hpp"
#include "ICycleSetter.hpp"

class ICycleGetter : public ICycleSetter {
public:
    virtual std::string get_left_time() = 0;
    virtual std::string get_cycle_state() = 0;
    virtual int get_general_count() = 0;
    virtual int get_current_number() = 0;
};

#endif