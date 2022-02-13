#ifndef IAUDIO_MODULE_HPP
#define IAUDIO_MODULE_HPP

class IAudioModule {
public:
    virtual void play() = 0;
    virtual void stop() = 0;
};

#endif