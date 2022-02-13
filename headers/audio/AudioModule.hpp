#ifndef AUDIO_MODULE
#define AUDIO_MODULE

#include "IAudioModule.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <string>
#include <map>

class AudioModule : public IAudioModule {
public:
    AudioModule();
    virtual ~AudioModule();

    virtual void play();
    virtual void stop();
private:

    struct Info {
        unsigned int ID;
        std::string filename;
        unsigned int rate;
        unsigned int format;
    };

    ALCdevice* device;
    ALCcontext* context;

    typedef std::map<ALuint, Info> TBuf;

    TBuf buffers;

    //идентификатор источника
    ALuint sourceID;

    void createSource();

    void loadWavFile(std::string); 
};

#endif