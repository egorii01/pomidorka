#include "../../../headers/gui/window/SettingsWindow.hpp"

SettingsWindow::SettingsWindow(Controller* controller) {
    set_controller(controller);
    initSettingsWindow();
    initStartView();
    initControllerEvents();
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::initSettingsWindow() {
    //инициализация окна настроек
    this -> set_resizable(false);
    this -> set_title("Settings");
    
    settingsMainBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL);
    settingsVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    settingsVBox -> set_border_width(50);
    this -> add(*settingsMainBox);

    settingsMainBox -> pack_start(*settingsVBox);
    settingsVBox -> set_halign(Gtk::Align::ALIGN_CENTER);
    settingsVBox -> set_valign(Gtk::Align::ALIGN_CENTER);

    //блок радиокнопок
    radioButtonsHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 20);
    twentyFiveCycleButton = new Gtk::RadioButton(radioButtonGroup, "Standart \"pomodoro\"");
    ninetyCycleButton = new Gtk::RadioButton(radioButtonGroup, "90/30");
    userCycleButton = new Gtk::RadioButton(radioButtonGroup, "Custom");

    radioButtonsHBox -> pack_start(*twentyFiveCycleButton);
    radioButtonsHBox -> pack_start(*ninetyCycleButton);
    radioButtonsHBox -> pack_end(*userCycleButton);

    settingsVBox -> pack_start(*radioButtonsHBox);

    radioButtonsHBox -> set_valign(Gtk::Align::ALIGN_START);
    radioButtonsHBox -> set_halign(Gtk::Align::ALIGN_CENTER);
    radioButtonsHBox -> show_all();

    //блок установки количества циклов
    cyclesCountHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 15);
    cyclesCountLabel = new Gtk::Label("Cycles count:");
    cyclesCountAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::
        create(5.0, 1.0, 25.0));
    cyclesCountSpin = new Gtk::SpinButton(*cyclesCountAdjustment);

    cyclesCountHBox -> pack_start(*cyclesCountLabel);
    cyclesCountHBox -> pack_start(*cyclesCountSpin);

    settingsVBox -> pack_start(*cyclesCountHBox);
    cyclesCountHBox -> set_halign(Gtk::Align::ALIGN_CENTER);
    cyclesCountHBox -> set_valign(Gtk::Align::ALIGN_CENTER);

    //блок установки кастомного рабочего времени
    workingTimerHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10);
    workingTimerFrame = new Gtk::Frame("Work time");
    workingTimerHoursVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    workingTimerMinutesVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    workingTimerSecondsVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    workingHours = new Gtk::Label("Hours");
    workingMinutes = new Gtk::Label("Minutes");
    workingSeconds = new Gtk::Label("Seconds");
    
    hoursAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(0.0, 0.0, 10.0));
    minutesAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(25.0, 0.0, 59.0));
    secondsAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(0.0, 0.0, 59.0));

    workingHoursSpin = new Gtk::SpinButton(*hoursAdjustment);
    workingMinutesSpin = new Gtk::SpinButton(*minutesAdjustment);
    workingSecondsSpin = new Gtk::SpinButton(*secondsAdjustment);

    workingTimerHoursVBox -> pack_start(*workingHours);
    workingTimerHoursVBox -> pack_start(*workingHoursSpin);

    workingTimerMinutesVBox -> pack_start(*workingMinutes);
    workingTimerMinutesVBox -> pack_start(*workingMinutesSpin);

    workingTimerSecondsVBox -> pack_start(*workingSeconds);
    workingTimerSecondsVBox -> pack_start(*workingSecondsSpin);

    workingTimerHBox -> pack_start(*workingTimerHoursVBox);
    workingTimerHBox -> pack_start(*workingTimerMinutesVBox);
    workingTimerHBox -> pack_start(*workingTimerSecondsVBox);

    workingTimerFrame -> add(*workingTimerHBox);
    settingsVBox -> pack_start(*workingTimerFrame);
    workingTimerFrame -> set_valign(Gtk::Align::ALIGN_CENTER);
    workingTimerFrame -> set_halign(Gtk::Align::ALIGN_CENTER);

    //блок установки времени перерыва
    relaxTimerHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10);
    relaxTimerFrame = new Gtk::Frame("Relax time");
    relaxTimerHoursVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    relaxTimerMinutesVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    relaxTimerSecondsVBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    relaxHours = new Gtk::Label("Hours");
    relaxMinutes = new Gtk::Label("Minutes");
    relaxSeconds = new Gtk::Label("Seconds");

    relaxHoursAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(0.0, 0.0, 2.0));
    relaxMinutesAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(5.0, 0.0, 59.0));
    relaxSecondsAdjustment = new Glib::RefPtr<Gtk::Adjustment>(Gtk::Adjustment::create(0.0, 0.0, 59.0));

    relaxHoursSpin = new Gtk::SpinButton(*relaxHoursAdjustment);
    relaxMinutesSpin = new Gtk::SpinButton(*relaxMinutesAdjustment);
    relaxSecondsSpin = new Gtk::SpinButton(*relaxSecondsAdjustment);

    relaxTimerHoursVBox -> pack_start(*relaxHours);
    relaxTimerHoursVBox -> pack_start(*relaxHoursSpin);

    relaxTimerMinutesVBox -> pack_start(*relaxMinutes);
    relaxTimerMinutesVBox -> pack_start(*relaxMinutesSpin);

    relaxTimerSecondsVBox -> pack_start(*relaxSeconds);
    relaxTimerSecondsVBox -> pack_start(*relaxSecondsSpin);

    relaxTimerHBox -> pack_start(*relaxTimerHoursVBox);
    relaxTimerHBox -> pack_start(*relaxTimerMinutesVBox);
    relaxTimerHBox -> pack_start(*relaxTimerSecondsVBox);

    relaxTimerFrame -> add(*relaxTimerHBox);
    settingsVBox -> pack_start(*relaxTimerFrame);
    relaxTimerFrame -> set_valign(Gtk::Align::ALIGN_CENTER);
    relaxTimerFrame -> set_halign(Gtk::Align::ALIGN_CENTER);

    //блок управления диалоговым окном
    settingsButtonHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10);
    okButton = new Gtk::Button("OK");
    applyButton = new Gtk::Button("Apply");
    cancelButton = new Gtk::Button("Cancel");

    settingsButtonHBox -> pack_start(*okButton);
    settingsButtonHBox -> pack_start(*applyButton);
    settingsButtonHBox -> pack_start(*cancelButton);

    settingsMainBox -> pack_start(*settingsButtonHBox);
    settingsButtonHBox -> set_halign(Gtk::Align::ALIGN_END);
    settingsButtonHBox -> set_valign(Gtk::Align::ALIGN_END);
}

void SettingsWindow::initControllerEvents() {
    twentyFiveCycleButton -> signal_toggled().connect(sigc::bind<SelectedRadioButton>(
        sigc::mem_fun(*this, &SettingsWindow::changeView), STANDART_MODE
    ));
    ninetyCycleButton -> signal_toggled().connect(sigc::bind<SelectedRadioButton>(
        sigc::mem_fun(*this, &SettingsWindow::changeView), LONG_MODE
    ));
    userCycleButton -> signal_toggled().connect(sigc::bind<SelectedRadioButton>(
        sigc::mem_fun(*this, &SettingsWindow::changeView), CUSTOM_MODE
    ));

    okButton -> signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::onOkButtonClicked));
    applyButton -> signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::onApplyButtonClicked));
    cancelButton -> signal_clicked().connect(sigc::mem_fun(*this, &SettingsWindow::onCancelButtonClicked));

    this -> signal_hide().connect(sigc::mem_fun(*this, &SettingsWindow::initStartView));
    
}

void SettingsWindow::changeView(SelectedRadioButton signal) {
    switch(signal) {
        case STANDART_MODE:
        {  
            enableSpinButtons(false);
            setSpinButtonsText(0, 25, 0, 0, 5, 0);
            break;
        }
        case LONG_MODE:
        {
            enableSpinButtons(false);
            setSpinButtonsText(1, 30, 0, 0, 30, 0);
            break;
        }
        case CUSTOM_MODE:
        {
            enableSpinButtons(true);
            break;
        }
    }
}

void SettingsWindow::setSpinButtonsText(int wHours, int wMinutes, int wSeconds, int rHours,
    int rMinutes, int rSeconds) {
    
    workingHoursSpin -> set_text(std::to_string(wHours));
    workingMinutesSpin -> set_text(std::to_string(wMinutes));
    workingSecondsSpin -> set_text(std::to_string(wSeconds));
    relaxHoursSpin -> set_text(std::to_string(rHours));
    relaxMinutesSpin -> set_text(std::to_string(rMinutes));
    relaxSecondsSpin -> set_text(std::to_string(rSeconds));
}

void SettingsWindow::sendSignalToController(std::string signal) {
    controller -> execute(signal);
}

void SettingsWindow::initStartView() {
    SettingsData loadedConfig = model -> get_config();
    switch (loadedConfig.mode) {
        case 1:
        {  
            twentyFiveCycleButton -> set_active(true);
            enableSpinButtons(false);
            break;
        }
        case 2:
        {
            ninetyCycleButton -> set_active(true);
            enableSpinButtons(false);
            break;
        }
        case 3:
        {
            userCycleButton -> set_active(true);
            enableSpinButtons(true);
            break;
        }
    }

    cyclesCountSpin -> set_text(std::to_string(loadedConfig.cyclesCount));

    setSpinButtonsText(loadedConfig.worksHours, loadedConfig.worksMinutes,
        loadedConfig.worksSeconds, loadedConfig.relaxHours, loadedConfig.relaxMinutes,
        loadedConfig.relaxSeconds);
}



void SettingsWindow::enableSpinButtons(bool state = true) {
    workingHoursSpin -> set_sensitive(state);
    workingMinutesSpin -> set_sensitive(state);
    workingSecondsSpin -> set_sensitive(state);

    relaxHoursSpin -> set_sensitive(state);
    relaxMinutesSpin -> set_sensitive(state);
    relaxSecondsSpin -> set_sensitive(state);
}

void SettingsWindow::notification(Notification message) {
    switch(message) {
        
    }
}

SettingsData SettingsWindow::getSettingsData() {
    SettingsData newConfig;
    
    if (twentyFiveCycleButton -> get_active()) {
        newConfig.mode = 1;
    }
    else if (ninetyCycleButton -> get_active()) {
        newConfig.mode = 2;
    }
    else if (userCycleButton -> get_active()) {
        newConfig.mode = 3;
    }

    newConfig.cyclesCount = std::stoi(cyclesCountSpin -> get_text());
    newConfig.worksHours = std::stoi(workingHoursSpin -> get_text());
    newConfig.worksMinutes = std::stoi(workingMinutesSpin -> get_text());
    newConfig.worksSeconds = std::stoi(workingSecondsSpin -> get_text());

    newConfig.relaxHours = std::stoi(relaxHoursSpin -> get_text());
    newConfig.relaxMinutes = std::stoi(relaxMinutesSpin -> get_text());
    newConfig.relaxSeconds = std::stoi(relaxSecondsSpin -> get_text());

    if (newConfig.worksHours == 0 && newConfig.worksMinutes == 0 && 
        newConfig.worksSeconds == 0) {
        
        workingSecondsSpin -> set_text("1");
        newConfig.worksSeconds = 1;
    }

    if (newConfig.relaxHours == 0 && newConfig.relaxMinutes == 0 && 
        newConfig.relaxSeconds == 0) {
        
        relaxSecondsSpin -> set_text("1");
        newConfig.relaxSeconds = 1;
    }

    return newConfig;
}

void SettingsWindow::onOkButtonClicked() {
    sendSignalToController("settings apply and close");
    initStartView();
}

void SettingsWindow::onApplyButtonClicked() {
    sendSignalToController("settings apply");
}

void SettingsWindow::onCancelButtonClicked() {
    initStartView();
    sendSignalToController("settings closed");
}