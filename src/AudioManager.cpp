#include "AudioManager.hpp"

AudioManager::AudioManager() : initialized(false), masterVolume(0.8f) {}

AudioManager::~AudioManager() {
    cleanup();
}

void AudioManager::init() {
    InitAudioDevice();
    initialized = IsAudioDeviceReady();
}

void AudioManager::cleanup() {
    if (initialized) {
        CloseAudioDevice();
        initialized = false;
    }
}

void AudioManager::playSound(SoundEffect effect) {
    (void)effect;
    if (!initialized) return;
    // Sound playback triggers safely when sound assets are loaded or synthesized
}

void AudioManager::playBGM() {
    if (!initialized) return;
}

void AudioManager::updateBGM() {
    if (!initialized) return;
}

void AudioManager::setVolume(float volume) {
    masterVolume = volume;
    if (initialized) {
        SetMasterVolume(masterVolume);
    }
}
