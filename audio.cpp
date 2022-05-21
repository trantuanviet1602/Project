#include "audio.hpp"
#include <iostream>
using namespace std;

bool Audio::initialize()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)<0)
    {
        cout<<"Could not initialize SDL_mixer";
        return false;
    }
    else return true;
}

void Audio::initializeAudio()
{
    menuMusic = Mix_LoadMUS("Music/Menu.mp3");
    gameMusic = Mix_LoadMUS("Music/Game.mp3");
    gameOver = Mix_LoadWAV("Music/GameOver.mp3");
    drop = Mix_LoadWAV("Music/drop.mp3");
    nextLevel = Mix_LoadWAV("Music/NextLevel.mp3");
    Mix_VolumeChunk(drop, 15);
    Mix_VolumeChunk(nextLevel, 15);
    Mix_VolumeChunk(gameOver, 15);
}

void Audio::pause()
{
    Mix_PauseMusic();
    Mix_Pause(-1);
}

void Audio::resume()
{
    Mix_ResumeMusic();
}

void Audio::playMenuMusic()
{
    Mix_HaltMusic();
    if(Mix_PlayingMusic()==0)
    {
        Mix_PlayMusic(menuMusic, -1);
    }
}

void Audio::playGameMusic()
{
    Mix_HaltMusic();
    if(Mix_PlayingMusic()==0)
    {
        Mix_PlayMusic(gameMusic, -1);
    }
}

void Audio::playDropEffect()
{
    Mix_PlayChannel(-1, drop, 0);
}

void Audio::playNextLvEffect()
{

    Mix_PlayChannel(-1, nextLevel, 0);
}

void Audio::playGameOverEffect()
{
    Mix_PlayChannel(-1, gameOver, 0);
}

void Audio::quit()
{
    Mix_FreeChunk(gameOver);
    Mix_FreeChunk(drop);
    Mix_FreeChunk(nextLevel);
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(gameMusic);

    Mix_Quit();
}
