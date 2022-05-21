#pragma once
#ifndef MENU_H_
#define MENU_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class Menu
{
private:
    enum{ScreenW = 400, ScreenH = 640};
    //setup SDL
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* menuTexture = NULL, *classicTexture = NULL, *blindTexture = NULL, *quitTexture = NULL;
    SDL_Surface* loadSurf = NULL;
    TTF_Font* font = NULL;
    SDL_Rect classicR, desClassicR, blindR, desBlindR, quitR, desQuitR;
    const SDL_Color WHITE = {255,255,255}, YELLOW = {255,255,0};



    SDL_Event e;
    int playerChoices = 0;
    bool running = false;
    bool written = false;
    bool runningGame = false;
    bool runningBlindGame = false;
public:
    bool isRunning()
    {
        return running;
    }
    bool runGame()
    {
        return runningGame;
    }
    bool runBlindGame()
    {
        return runningBlindGame;
    }
    bool initialize(const char* title);
    void write();
    void initializeMenu();
    void updateRender();
    void handleEvent();
    void quit();
    void menu();
};


#endif // MENU_H_
