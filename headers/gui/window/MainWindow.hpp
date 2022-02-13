#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "AbstractWindow.hpp"
#include "../../observers/Observer.hpp"
#include <gtkmm.h>

class MainWindow : public AbstractWindow, public Gtk::Window {
public:
    MainWindow(Controller*);
    virtual ~MainWindow();

    virtual void notification(Notification);

private:
	void updateWindow();
    void initMainWindow();
	void initControllerEvents();
	void sendSignalToController(std::string);
	int showDialog(std::string, std::string);

	bool responseChangesFromModel();

    Gtk::Box* hBoxGeneral;
	Gtk::Box* vBoxLeft;
	Gtk::Box* vBoxRight;

	Gtk::Label* cycleStatus;
	Gtk::Label* timeLeftLabel;
	Gtk::Box* buttonsHBox;

	Gtk::Button* startButton;
	Gtk::Button* stopButton;

	Gtk::Label* cycleNumberLabel;
	Gtk::Label* counterStatusLabel;
	Gtk::Button* settingsButton;
};

#endif