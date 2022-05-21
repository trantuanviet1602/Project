#pragma once
#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL.h>
#include <SDL_image.h>
#include "game.hpp"
#include <SDL_ttf.h>
#include <sstream>

class Graphic
{
private:
    int currentLevel = 600;
    enum { ScreenW = 400, ScreenH = 640 };
    enum {Lines = 20, Cols = 10};
    enum {BlockW = 24, BlockH = 24 };

    int highScore[5];
    TTF_Font* font = NULL;
    const SDL_Color WHITE = {255,255,255};

	SDL_Rect srcR = { 0, 0, BlockW, BlockH }, destR = { 0, 0, BlockW, BlockH },
             srcHoldR = { 0, 0, BlockW, BlockH }, destHoldR = { 0, 0, BlockW, BlockH },
             srcNextR = { 0, 0, BlockW, BlockH }, destNextR = { 0, 0, BlockW, BlockH },
             srcPredictionR = { 0, 0, BlockW, BlockH }, destPredictionR = { 0, 0, BlockW, BlockH },
             writeR, desWriteR, levelR, desLevelR, highR, desHighR;

    SDL_Event e;

    Game game_;
    bool blindFolded = false;

    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* loadSurf = NULL;
    SDL_Texture* background = NULL, * blocks = NULL, *blindBlocks= NULL, *predictionBlocks = NULL, *scoreTexture= NULL, *levelTexture = NULL,
                * pauseBackground = NULL,  *highScoreTexture = NULL;


public:
    Graphic()
    {

    }
    ~Graphic()
    {

    }
    bool isrunning()
	{
		return game_.running;
	}
	bool quit()
	{
	    return game_.quit;
	}
	bool isPaused()
	{
	    return game_.pausing;
	}
	int getScore()
	{
	    return game_.score;
	}

	bool playDropSound()
	{
	    return game_.dropSound;
	}

    bool initialize(const char* title, bool blindfolded);
    void initializeGame(int scoreTemp[]);

    void setRectPos(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void moveRectPos(SDL_Rect& rect, int x, int y);

	bool checkForPrediction();
	void updateRender();
	void updateBlindRender();
    void play();
	void clean();
    void write();

    bool nextLevelSound = true;

};

#endif // GRAPHICS_H_
