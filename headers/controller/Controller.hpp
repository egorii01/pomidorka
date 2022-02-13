#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>

class Controller {
public:
    virtual void execute(std::string) = 0;
};

#endif