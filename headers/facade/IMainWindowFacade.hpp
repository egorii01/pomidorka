#ifndef IMAIN_WINDOW_FACADE_HPP
#define IMAIN_WINDOW_FACADE_HPP

class IMainWindowFacade {
public:
    virtual void start_countdown() = 0;
    virtual void stop_countdown() = 0;
    virtual void continue_countdown() = 0;
};

#endif