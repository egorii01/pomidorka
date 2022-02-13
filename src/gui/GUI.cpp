#include "../../headers/gui/GUI.hpp"

#include <iostream>

GUI::GUI() {
    main_window = new MainWindow(this);
    settings_window = new SettingsWindow(this);
    
    try {
        audio_module = new AudioModule();
    }
    catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }

    model = AppModel::get_instance();
}

GUI::~GUI() {
    delete settings_window;
    delete main_window;
}

void GUI::execute(std::string event) {
    if (event == "start timer") {
        model -> start_countdown();
    }
    if (event == "stop timer") {
        model -> stop_countdown();
    }
    if (event == "open settings window") {
        settings_window -> show_all();
    }
    if (event == "settings apply and close") {
        SettingsData newConfig = settings_window -> getSettingsData();
        model -> save_config(newConfig);
        settings_window -> close();
    }
    if (event == "settings apply") {
        SettingsData newConfig = settings_window -> getSettingsData();
        model -> save_config(newConfig);
    }
    if (event == "settings closed") {
        settings_window -> close();
    }
    if (event == "continue countdown") {
        model -> continue_countdown();
    }
}

Gtk::Window* GUI::get_main_window() {
    return main_window;
}