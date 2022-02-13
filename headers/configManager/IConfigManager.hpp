#ifndef ICONFIG_MANAGER_HPP
#define ICONFIG_MANAGER_HPP

#include "../data/SettingsData.hpp"

class IConfigManager {
public:
    virtual void save_config(SettingsData) = 0;
    virtual SettingsData load_config() = 0;
};

#endif