#include <thread>
#include <chrono>
#include <gtkmm.h>

#include "headers/gui/GUI.hpp"

int main(int argc, char* argv[]) {

    auto app = Gtk::Application::create();

    GUI application;

    return app -> run(*(application.get_main_window()), argc, argv);
}