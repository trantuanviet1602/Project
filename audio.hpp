#pragma once
#ifndef AUDIO_H_
#define AUDIO_H_
#include <SDL_mixer.h>

class Audio
{
private:
    Mix_Music* menuMusic = NULL;
    Mix_Music* gameMusic = NULL;
    Mix_Chunk* gameOver = NULL;
    Mix_Chunk* drop = NULL;
    Mix_Chunk* nextLevel = NULL;
public:
    bool initialize();
    void initializeAudio();
    void pause();
    void resume();
    void playMenuMusic();
    void playGameMusic();
    void playDropEffect();
    void playNextLvEffect();
    void playGameOverEffect();
    void quit();
};
#endif // AUDIO_H_
