#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <fstream>
#include <string>
#include "IConfigManager.hpp"

class ConfigManager : public IConfigManager {
public:
    ConfigManager();
    virtual ~ConfigManager();

    virtual void save_config(SettingsData);
    virtual SettingsData load_config();

private:
    void save_default_config();

    std::ofstream configOutput;
    std::ifstream configInput;

    SettingsData configBuffer;

    static std::string fileName;
};

#endif