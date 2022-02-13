#include "../../../headers/gui/window/AbstractWindow.hpp"

AbstractWindow::AbstractWindow() {
    model = AppModel::get_instance();
    model -> registerObserver(this);
}

AbstractWindow::~AbstractWindow() {

}

void AbstractWindow::set_controller(Controller* controller) {
    this -> controller = controller;
}