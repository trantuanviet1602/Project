#pragma once
#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class GameOver
{
private:
    enum{ScreenH = 640, ScreenW = 400};

    //setup SDL
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* gameOverTexture = NULL, *restartTexture = NULL, *mainTexture = NULL, *backTexture = NULL;
    SDL_Surface* loadSurf = NULL;
    TTF_Font* font = NULL;
    SDL_Rect restartGameR, desRestartGameR, backR, desbackR, mainR, desMainR;
    const SDL_Color WHITE = {255,255,255}, YELLOW = {255,255,0};
    SDL_Event e;



    int playerChoices = 0;
    bool running = false;
    bool written = false;
    bool runningGame = false;
    bool menuRunning = false;
    bool cfquit = false;
public:
    bool isRunning()
    {
        return running;
    }
    bool runGame()
    {
        return runningGame;
    }
    bool runMenu()
    {
        return menuRunning;
    }
    bool confirmQuit()
    {
        return cfquit;
    }
    bool initialize(const char* title);
    void write();
    void initializeScreen();
    void updateRender();
    void handleEvent();
    void quit();
    void gameOver();
};


#endif // GAMEOVER_H_
