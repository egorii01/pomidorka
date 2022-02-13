#ifndef ICONFIG_MANAGER_FACADE_HPP
#define ICONFIG_MANAGER_FACADE_HPP

#include "../data/SettingsData.hpp"

class IConfigManagerFacade {
public:
    virtual void save_config(SettingsData) = 0;
};

#endif