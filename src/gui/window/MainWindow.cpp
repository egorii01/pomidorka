#include "../../../headers/gui/window/MainWindow.hpp"

MainWindow::MainWindow(Controller* controller) {
    set_controller(controller);
    initMainWindow();
    initControllerEvents();
}

MainWindow::~MainWindow() {

    delete hBoxGeneral;
    delete vBoxLeft;
	delete vBoxRight;

	delete cycleStatus;
	delete timeLeftLabel;
	delete buttonsHBox;

	delete startButton;
	delete stopButton;

	delete cycleNumberLabel;
	delete counterStatusLabel;
	delete settingsButton;
    
}

void MainWindow::initMainWindow() {

    this -> set_title("Pomidorka by Egorka");
    this -> set_resizable(false);
    this -> set_border_width(50);

    hBoxGeneral = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10);
    vBoxLeft = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);
    vBoxRight = new Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 10);

    this -> add(*hBoxGeneral);
    hBoxGeneral -> set_halign(Gtk::Align::ALIGN_CENTER);
    hBoxGeneral -> set_valign(Gtk::Align::ALIGN_CENTER);

    cycleStatus = new Gtk::Label(model -> get_cycle_state());
    timeLeftLabel = new Gtk::Label(model -> get_left_time());
    cycleStatus -> show();
    timeLeftLabel -> show();

    buttonsHBox = new Gtk::Box(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10);
    startButton = new Gtk::Button("Start");
    stopButton = new Gtk::Button("Stop");
    
    buttonsHBox -> pack_start(*startButton);
    buttonsHBox -> pack_end(*stopButton);
    
    startButton -> show();
    stopButton -> show();

    vBoxLeft -> pack_start(*cycleStatus);
    vBoxLeft -> pack_start(*timeLeftLabel);
    vBoxLeft -> pack_start(*buttonsHBox);
    vBoxLeft -> show();

    cycleNumberLabel = new Gtk::Label("Cycle number:");
    std::string counterStatusInfo = std::to_string(model -> get_current_number()) +
    "/" + std::to_string(model -> get_general_cycles_count());
    counterStatusLabel = new Gtk::Label(counterStatusInfo);
    settingsButton = new Gtk::Button("Settings");

    vBoxRight -> pack_start(*cycleNumberLabel);
    vBoxRight -> pack_start(*counterStatusLabel);
    vBoxRight -> pack_end(*settingsButton);

    vBoxRight -> show_all();

    hBoxGeneral -> pack_start(*vBoxLeft);
    hBoxGeneral -> pack_end(*vBoxRight);
    hBoxGeneral -> show_all();
}

void MainWindow::initControllerEvents() {
    
    //присоединение функции, которая будет выполняться в режиме ожидания
    Glib::signal_idle().connect(sigc::mem_fun(*this, 
        &MainWindow::responseChangesFromModel));

    startButton -> signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this, 
        &MainWindow::sendSignalToController), "start timer"));

    stopButton -> signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this,
        &MainWindow::sendSignalToController), "stop timer"));

    settingsButton -> signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this, 
        &MainWindow::sendSignalToController), "open settings window"));
}

void MainWindow::notification(Notification message) {
    switch(message) {
        case COUNTDOWN_STOPPED:
        case LEFT_TIME_CHANGED:
        case CONFIG_CHANGED:
        {
            updateWindow();
            break;
        }
        case CYCLE_ENDS:
        case CYCLE_PAUSED:
        {
            int answer;

            if (message == CYCLE_PAUSED) {
                answer = showDialog("Working time has expired!", 
                    "Do you want to start relax timer?");
            }
            else if (message == CYCLE_ENDS) {
                answer = showDialog("Relax time has expired!",
                    "Do you want to start working?");
            }

            switch (answer) {
                case Gtk::RESPONSE_YES:
                {   
                    sendSignalToController("stop sound");
                    sendSignalToController("continue countdown");
                    break;
                }
                case Gtk::RESPONSE_NO:
                {
                    sendSignalToController("stop sound");
                    sendSignalToController("stop timer");
                    break;
                }
            }
            break;
        }
        case COUNTDOWN_ENDS:
        {
            Gtk::MessageDialog changeStateDialog(*this, "Stop working!", false, 
                Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
            changeStateDialog.set_secondary_text("Let's go to drink beer...");

            //диалог отображается поверх других окон
            this -> present();
            changeStateDialog.set_keep_above();
            sendSignalToController("play sound");


            int answer = changeStateDialog.run();

            if (answer == Gtk::RESPONSE_OK) {
                sendSignalToController("stop sound");
                updateWindow();
            }
            break;
        }
    }
}

void MainWindow::sendSignalToController(std::string signal) {
    controller -> execute(signal);
}

int MainWindow::showDialog(std::string primaryText, std::string secondaryText) {

    Gtk::MessageDialog changeStateDialog(*this, primaryText, false, 
        Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
    changeStateDialog.set_secondary_text(secondaryText);

    //диалог отображается поверх остальных окон
    this -> present();
    changeStateDialog.set_keep_above();

    int answer = changeStateDialog.run();

    sendSignalToController("play sound");

    return answer;
}

void MainWindow::updateWindow() {
    cycleStatus -> set_text(model -> get_cycle_state());
    timeLeftLabel -> set_text(model -> get_left_time());
            
    std::string counterStatusInfo = std::to_string(model -> get_current_number()) +
        "/" + std::to_string(model -> get_general_cycles_count());
    counterStatusLabel -> set_text(counterStatusInfo);
}

bool MainWindow::responseChangesFromModel() {

    Notification message = model -> get_notification();

    while (message != EMPTY_NOTIFICATION) {
        switch(message) {
            case COUNTDOWN_STOPPED:
            case LEFT_TIME_CHANGED:
            case CONFIG_CHANGED:
            {
                updateWindow();
                break;
            }
            case CYCLE_ENDS:
            case CYCLE_PAUSED:
            {
                int answer;

                if (message == CYCLE_PAUSED) {
                    answer = showDialog("Working time has expired!", 
                        "Do you want to start relax timer?");
                }
                else if (message == CYCLE_ENDS) {
                    answer = showDialog("Relax time has expired!",
                        "Do you want to start working?");
                }

                switch (answer) {
                    case Gtk::RESPONSE_YES:
                    {
                        sendSignalToController("continue countdown");
                        break;
                    }
                    case Gtk::RESPONSE_NO:
                    {
                        sendSignalToController("stop timer");
                        break;
                    }
                }
                break;
            }
            case COUNTDOWN_ENDS:
            {
                Gtk::MessageDialog changeStateDialog(*this, "Stop working!", false, 
                    Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
                changeStateDialog.set_secondary_text("Let's go to drink beer...");

                int answer = changeStateDialog.run();

                if (answer == Gtk::RESPONSE_OK) {
                    sendSignalToController("stop timer");
                    updateWindow();
                }

                break;
            }
            
        }

        message = model -> get_notification();
    }

    //метод перестает отрабатывать при закрытии главного окна
    return this -> get_visible();
}