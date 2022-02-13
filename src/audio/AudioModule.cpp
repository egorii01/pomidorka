#include "../../headers/audio/AudioModule.hpp"
#include <iostream>

#include <exception>

AudioModule::AudioModule() {

    ALfloat listenerPosition[] = {0.0, 0.0, 0.0};
    ALfloat listenerVelocity[] = {0.0, 0.0, 0.0};
    ALfloat listenerOrientation[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

    //Открытие заданного по умолчанию устройства
    device = alcOpenDevice(nullptr);
    if (!device) {
        throw std::runtime_error("Open device error");
    }

    //создание контекста
    context = alcCreateContext(device, nullptr);
    if (alcGetError(device) != AL_NO_ERROR) {
        throw std::runtime_error("Create context error");
    }
    
    //объявление контекста текущим
    alcMakeContextCurrent(context);

    //установка параметров слушателя
    alListenerfv(AL_POSITION, listenerPosition);
    alListenerfv(AL_VELOCITY, listenerVelocity);
    alListenerfv(AL_ORIENTATION, listenerOrientation);

    try {
        createSource();
    }
    catch(std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }

}

AudioModule::~AudioModule() {

    //очистка буферов
    for (TBuf::iterator i = buffers.begin(); i != buffers.end(); i++) {
        alDeleteBuffers(1, &i -> second.ID);
    }

    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    alSourceStop(sourceID);
    if (alIsSource(sourceID)) {
        alDeleteSources(1, &sourceID);
    }
}

void AudioModule::play() {
    alSourcePlay(sourceID);
}

void AudioModule::stop() {
    alSourceStop(sourceID);
}

void AudioModule::createSource() {
    alGenSources(1, &sourceID);

    if (alcGetError(device) != AL_NO_ERROR) {
        throw std::runtime_error("Source not creates");
    }

    ALfloat sourcePosition[] = {0.0, 0.0, -1.0};
    ALfloat sourceVelocity[] = {0.0, 1.0, 0.0};

    alSourcef(sourceID, AL_PITCH, 1.0f);
    alSourcef(sourceID, AL_GAIN, 1.0f);
    alSourcefv(sourceID, AL_POSITION, sourcePosition);
    alSourcefv(sourceID, AL_VELOCITY, sourceVelocity);
    alSourcei(sourceID, AL_LOOPING, 1);

    try {
        loadWavFile("../../assets/signal.wav");
    }
    catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }
}

void AudioModule::loadWavFile(std::string filename) {
    Info buffer;
    ALenum format;
    ALvoid* data;
    ALsizei size;
    ALsizei freq;
    ALboolean loop;

    ALuint bufID = 0;

    buffer.filename = filename;

    for (TBuf::iterator i = buffers.begin(); i != buffers.end(); i++) {
        if (i -> second.filename == filename) {
            bufID = i -> first;
        }
    }

    if (!bufID) {
        alGenBuffers(1, &buffer.ID);

        if (alcGetError(device) != AL_NO_ERROR) {
            throw std::runtime_error("Go to nahui with your errors!!!");
        }
        alutLoadWAVFile((ALbyte*) filename.data(), &format, &data, &size, &freq, &loop);

        if (alcGetError(device) != AL_NO_ERROR) {
            throw std::runtime_error("Some error");
        }
        buffer.format = format;
        buffer.rate = freq;

        alBufferData(buffer.ID, format, data, size, freq);
        if (alcGetError(device) != AL_NO_ERROR) {
            throw std::runtime_error("Buffer data error");
        }

        alutUnloadWAV(format, data, size, freq);
        if (alcGetError(device) != AL_NO_ERROR) {
            throw std::runtime_error("Unload wav error");
        }
    } 

    buffers[buffer.ID] = buffer;

    alSourcei(sourceID, AL_BUFFER, buffer.ID);
}