#ifndef GUI_HPP
#define GUI_HPP

#include "../controller/Controller.hpp"
#include "window/MainWindow.hpp"
#include "window/SettingsWindow.hpp"
#include "../facade/IFacade.hpp"
#include "../audio/IAudioModule.hpp"

#include "../model/AppModel.hpp"
#include "../audio/AudioModule.hpp"

class GUI : public Controller {
public:
    GUI();
    virtual ~GUI();

    Gtk::Window* get_main_window();

    virtual void execute(std::string);
private:
    MainWindow* main_window;
    SettingsWindow* settings_window;
    IFacade* model;
    IAudioModule* audio_module;
};

#endif