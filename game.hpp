#pragma once
#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
using namespace std;
class Game
{
private:
    SDL_Event e;
    Uint32 startTime = 0, currentTime = 0;
    const Uint8 *state = NULL;
    unsigned int delay = 600;
    int downBottom = 0;
    static const int figures[7][4];
    int dx=0;
    int countHold = 0;
    bool continueMoving = true;

public:
	enum { Lines = 20, Cols = 10 };
    Game()
	{
	}
	~Game()
	{
	}

	void setCurrentTime(Uint32 t)
	{
		currentTime = t;
	}


	//About Tetriminos
	void hold(int &countHolds);
	void next();
	void nextTetrimino();



	void handleEvents();

	void gameplay();
	bool gameOver();

	void move(bool &continueMove);
	void tick();

    //rotation
	void rotate();
	int checkRotation();

    //check lines, get score, and get level.
	void unite();
	void delayTime();

    //reset
    void reset();
    void resetPrediction();
    void resetCoordinates();


    //Validation
    bool isvalid();
	bool fieldValid();
    bool isValidForPrediction();
    void getPredictPosition();



    //public variables for graphic.
    int written = 0;
    bool watch = false;
    unsigned int level = 600;
	int field[Lines][Cols] = {0};
	struct Point
	{
		int x, y, figure, colors;
		Point()
		{
		    x = -1;
		    y = -1;
		    figure = -1;
		    colors = -1;
		}
	}   items[4], backup[4], holdItems[4] , nextItems[4], predictionItems[4];
    bool running = false;
    bool quit = false;
    int score = -1;
    int pausing = 0;
    bool dropSound = true;
};

#endif // GAME_H_
