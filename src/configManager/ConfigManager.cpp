#include "../../headers/configManager/ConfigManager.hpp"

std::string ConfigManager::fileName = "config.dat";

ConfigManager::ConfigManager() {

}

ConfigManager::~ConfigManager() {

}

void ConfigManager::save_config(SettingsData config) {
    configBuffer = config;

    configOutput.open(fileName, std::ios::binary);
    configOutput.write((char*)&configBuffer, sizeof(SettingsData));
    configOutput.close();
}

SettingsData ConfigManager::load_config() {
    configInput.open(fileName, std::ios::binary);
    
    if (configInput.is_open()) {
        configInput.read((char*)&configBuffer, sizeof(SettingsData));
    }
    else {
        save_default_config();
    }

    configInput.close();

    return configBuffer;
}

void ConfigManager::save_default_config() {
    SettingsData default_config;
    default_config.mode = 1;
    default_config.cyclesCount = 5;
    default_config.worksHours = 0;
    default_config.worksMinutes = 25;
    default_config.worksSeconds = 0;
    default_config.relaxHours = 0;
    default_config.relaxMinutes = 5;
    default_config.relaxSeconds = 0;

    save_config(default_config);
}