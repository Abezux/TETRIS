#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <raylib.h>

enum class SoundEffect {
    Move,
    Rotate,
    SoftDrop,
    HardDrop,
    LineClear,
    TetrisClear,
    GameOver,
    Hold
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void init();
    void cleanup();

    void playSound(SoundEffect effect);
    void playBGM();
    void updateBGM();
    void setVolume(float volume);

private:
    bool initialized;
    float masterVolume;
    Sound moveSound;
    Sound rotateSound;
    Sound dropSound;
    Sound clearSound;
    Sound tetrisSound;
    Sound gameoverSound;
    Music bgm;
};

#endif // AUDIOMANAGER_HPP
