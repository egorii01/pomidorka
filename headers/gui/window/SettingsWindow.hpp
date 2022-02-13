#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include "AbstractWindow.hpp"
#include "../../controller/Controller.hpp"
#include "../../observers/Observer.hpp"
#include "../../data/SettingsData.hpp"
#include <gtkmm.h>

class SettingsWindow : 
public AbstractWindow,
public Gtk::Window {
public:
    SettingsWindow(Controller*);
    virtual ~SettingsWindow();

    virtual void notification(Notification);

    SettingsData getSettingsData();
private:

	enum SelectedRadioButton {
		STANDART_MODE,
		LONG_MODE,
		CUSTOM_MODE,
	};

    void initSettingsWindow();
    void initControllerEvents();
	void changeView(SelectedRadioButton);
	void setSpinButtonsText(int, int, int, int, int, int);
    void sendSignalToController(std::string);
	void initStartView();
	void enableSpinButtons(bool);

	void onOkButtonClicked();
	void onApplyButtonClicked();
	void onCancelButtonClicked();

    Gtk::Box* settingsMainBox;
	Gtk::Box* settingsVBox;

	Gtk::Box* radioButtonsHBox;
	Gtk::RadioButton::Group radioButtonGroup;
	Gtk::RadioButton* twentyFiveCycleButton;
	Gtk::RadioButton* ninetyCycleButton;
	Gtk::RadioButton* userCycleButton;

	Gtk::Box* cyclesCountHBox;
	Gtk::Label* cyclesCountLabel;
	Glib::RefPtr<Gtk::Adjustment>* cyclesCountAdjustment;
	Gtk::SpinButton* cyclesCountSpin;

	Gtk::Box* workingTimerHBox;
	Gtk::Frame* workingTimerFrame;
	Gtk::Box* workingTimerHoursVBox;
	Gtk::Box* workingTimerMinutesVBox;
	Gtk::Box* workingTimerSecondsVBox;
	Gtk::Label* workingHours;
	Gtk::Label* workingMinutes;
	Gtk::Label* workingSeconds;
	Glib::RefPtr<Gtk::Adjustment>* hoursAdjustment;
	Glib::RefPtr<Gtk::Adjustment>* minutesAdjustment;
	Glib::RefPtr<Gtk::Adjustment>* secondsAdjustment;
	Gtk::SpinButton* workingHoursSpin;
	Gtk::SpinButton* workingMinutesSpin;
	Gtk::SpinButton* workingSecondsSpin;

	Gtk::Box* relaxTimerHBox;
	Gtk::Frame* relaxTimerFrame;
	Gtk::Box* relaxTimerHoursVBox;
	Gtk::Box* relaxTimerMinutesVBox;
	Gtk::Box* relaxTimerSecondsVBox;
	Gtk::Label* relaxHours;
	Gtk::Label* relaxMinutes;
	Gtk::Label* relaxSeconds;
	Glib::RefPtr<Gtk::Adjustment>* relaxHoursAdjustment;
	Glib::RefPtr<Gtk::Adjustment>* relaxMinutesAdjustment;
	Glib::RefPtr<Gtk::Adjustment>* relaxSecondsAdjustment;
	Gtk::SpinButton* relaxHoursSpin;
	Gtk::SpinButton* relaxMinutesSpin;
	Gtk::SpinButton* relaxSecondsSpin;

	Gtk::Box* settingsButtonHBox;
	Gtk::Button* okButton;
	Gtk::Button* applyButton;
	Gtk::Button* cancelButton;

};

#endif