#ifndef ABSTRACT_WINDOW_HPP
#define ABSTRACT_WINDOW_HPP

#include "../../observers/Observer.hpp"
#include "../../controller/Controller.hpp"
#include "../../model/IModel.hpp"

#include "../../model/AppModel.hpp"

class AbstractWindow : public Observer {
public:
    AbstractWindow();
    virtual ~AbstractWindow();

    virtual void set_controller(Controller*);

protected:
    Controller* controller;
    IModel* model;
};

#endif