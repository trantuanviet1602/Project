#include <iostream>
#include "game.hpp"
#include <sstream>
#include <windows.h>

using namespace std;
/*
	0	1	2	3
	4	5	6	7
*/



const int Game::figures[7][4] =
{
    0,1,5,6,	// Z
    2,6,5,4,	// L
    2,1,5,4,	// S
	0,1,2,3,	// I
	1,4,5,6,	// T
	0,4,5,6,	// J
	1,2,5,6,    // O
};

bool Game::gameOver()
{
    if(!fieldValid()&&items[0].figure!=-1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(items[i].y  <= 0) return true;
        }
    }
    return false;

}






void Game::reset()
{
    resetCoordinates();
    delay=level;
    countHold=0;
    downBottom=0;
    continueMoving=true;
}

void Game::next() //show next tetrimino.
{
    int n = rand() % 7;
    for (int i = 0; i < 4; i++)
    {
        nextItems[i].colors = n + 1 ;
        nextItems[i].figure= n;
        nextItems[i].x = figures[n][i] % 4+ Cols/2 - 2;    //center of map
        nextItems[i].y = int(figures[n][i] / 4);

    }
}

void Game::nextTetrimino()
{
    written = 0;
    unite();
    score++;
    reset();        //reset all index.
    if(!gameOver())
    {
        for(int i=0;i<4;i++)
        {
                //get the prediction tetrimino
            predictionItems[i].colors=nextItems[i].colors;
            predictionItems[i].figure=nextItems[i].figure;
            predictionItems[i].x=nextItems[i].x;
            predictionItems[i].y=nextItems[i].y;

        }
        getPredictPosition();
        for(int i = 0; i <4; i++)
        {
            //get the next tetrimino
            items[i].colors=nextItems[i].colors;
            items[i].figure=nextItems[i].figure;
            items[i].x=nextItems[i].x ;
            items[i].y=nextItems[i].y ;
        }

        next();     //generate next tetrimino.
    }
}

void Game::hold(int &countHolds)        //hold tetriminos and switch to another tetrimino which is held, or generate new tetrimino if there's no tetromino in hold.
{
    if(countHolds==0)
    {
        if(holdItems[0].figure==-1)
        {
            for(int i=0;i<4;i++)
            {
                holdItems[i].colors=items[i].colors;
                holdItems[i].figure=items[i].figure;
                holdItems[i].x=items[i].x;
                holdItems[i].y=items[i].y;
            }
            nextTetrimino();
        }
        else
        {
            Point temp[4];
            for(int i=0;i<4;i++)
            {
                predictionItems[i].x=holdItems[i].x;
                predictionItems[i].y=holdItems[i].y;

                //swap colors
                temp[i].colors=holdItems[i].colors;
                holdItems[i].colors=items[i].colors;
                items[i].colors=temp[i].colors;

                //swap figure
                temp[i].figure=holdItems[i].figure;
                holdItems[i].figure=items[i].figure;
                items[i].figure=temp[i].figure;

                //swap x coordinates
                temp[i].x=holdItems[i].x;
                holdItems[i].x=items[i].x;
                items[i].x=temp[i].x;

                //swap y coordinates
                temp[i].y=holdItems[i].y;
                holdItems[i].y=items[i].y;
                items[i].y=temp[i].y;
            }
            resetCoordinates();
        }
        countHold++;               //can hold 1 time per tetromino.
    }
}

void Game::resetCoordinates()
{
    for(int i=0;i<4;i++)
    {
        holdItems[i].x=figures[holdItems[i].figure][i] %4 + Cols/2 -2 ;// reset to the center of map
        holdItems[i].y=int(figures[holdItems[i].figure][i] /4);
    }
}







void Game::handleEvents()
{
    if(continueMoving==true)
    {

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
            {
                running = false;
                quit = true;
                break;
            }
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if(continueMoving)  rotate();
                    break;
                case SDLK_LEFT:
                    dx = -1;
                    break;
                case SDLK_RIGHT:
                    dx = 1;
                    break;
                case SDLK_p:
                    pausing=(pausing+1)%2;
                    break;
                case SDLK_o:
                    if(pausing == 0) hold(countHold);
                    break;
                case SDLK_i :
                {
                    if(pausing==0)
                    {
                        //immediately set the tetromino to bottom.
                        for(int i=0;i<4;i++)
                        {
                            items[i].x=predictionItems[i].x;
                            items[i].y=predictionItems[i].y;

                        }
                        continueMoving=false;
                        downBottom=1;
                    }
                    break;
                }
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
	state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_DOWN])
    {
        delay=50;
    }
    else if(state[SDL_SCANCODE_U])
    {
        watch = true;
    }
	else
    {
        watch = false;
        delay = level;
    }
}



//Validation


bool Game::fieldValid()
{
    for(int i=0;i<4;i++)
    {
        if(items[i].y < 0) continue;
        if(field[items[i].y+1][items[i].x]) return false;
    }
    return true;
}

bool Game::isvalid()
{
	for (int i = 0; i < 4; i++)
        {
            if (items[i].x < 0 || items[i].x >= Cols || items[i].y >= Lines)    return false;
            else
            {
                if (items[i].y < 0) continue;
                if (field[items[i].y][items[i].x]) return false;
            }
        }
	return true;
}

bool Game::isValidForPrediction()
{
    for (int i = 0; i < 4; i++)
    {
        if(predictionItems[i].y < 0) continue;
        if(predictionItems[i].y >= Lines - 1) return false;
        if(field[predictionItems[i].y + 1 ][predictionItems[i].x]) return false;
    }
	return true;
}


//Movement

void Game::getPredictPosition()
{
    for(int i=0;i<4;i++)
    {
        predictionItems[i].y = items[i].y;
        predictionItems[i].x = items[i].x;
    }
    while(isValidForPrediction())
    {
        for(int i=0;i<4;i++) predictionItems[i].y++;
    }

}

void Game::move(bool &continueMove)
{
    if(continueMove)
    {
        if(!fieldValid()) delay = max(500 - (score/100) * 10, 250);
        if (dx)
        {
            for (int i = 0; i < 4; i++)
            {
                items[i].x += dx;
            }

            if (!isvalid())
            {
                for (int i = 0; i < 4; i++) items[i] = backup[i];
            }
        }
        dx=0;
        getPredictPosition();
    }
}



//Rotation

void Game::rotate()
{

       Point p = items[2];	// center of rotation
        for (int i = 0; i < 4; i++)
        {
            int x = items[i].y - p.y;
            int y = items[i].x - p.x;
            items[i].x = p.x - x;
            items[i].y = p.y + y;
        }

        int n = checkRotation();
        for(int i=0;i<4;i++)
        {
            items[i].x+=n;
        }
        if(!isvalid()) for(int i=0;i<4;i++) items[i].y-=1;
        getPredictPosition();
}
int Game::checkRotation()
{
    int returning=0;
    for(int i=0;i<4;i++)
    {
            if(items[i].x>Cols-1)
            {
                if(returning > 9 - items[i].x) returning = 9 - items[i].x;
            }
            if(items[i].x<0)
            {
                if(returning < - items[i].x) returning = - items[i].x;
            }
    }

        return returning;
}




void Game::gameplay()
{

    if(!gameOver()&&pausing==0)
    {
            ////////// backup
            for (int i = 0; i < 4; i++) backup[i] = items[i];
            move(continueMoving);
            tick();
    }
}

void Game::tick()
{
        if (currentTime - startTime > delay)
        {
            for (int i = 0; i < 4; i++) backup[i] = items[i];
            for (int i = 0; i < 4; i++) items[i].y++;
            if (!isvalid())
            {
                for (int i = 0; i < 4; i++) field[backup[i].y][backup[i].x] = backup[i].colors;
                delayTime();
                nextTetrimino();
            }
            startTime = currentTime;
        }

}


void Game::delayTime()
{
    if(downBottom!=1)
    {
        SDL_Delay(200);
    }
}




void Game::unite()
{
    int countLines=0;
    int kMax = predictionItems[0].y;

    for(int i=0;i<4;i++)
    {
        if(kMax < predictionItems[i].y) kMax = predictionItems[i].y;
    }

    for (int i = kMax; i >= 0; i--)
    {
        int count = 0;
        for (int j = 0; j < Cols; j++)
        {
            if (field[i][j]) count++;
            field[kMax][j] = field[i][j];
        }
        if (count < Cols)   kMax--;
        else
        {
            countLines++;
            for(int k=0;k<Cols;k++)
            {
                field[0][k]=0;
            }
        }
    }
    switch(countLines)
    {
        case 1: score+=10; dropSound = false; break;
        case 2: score+=20; dropSound = false; break;
        case 3: score+=40; dropSound = false; break;
        case 4: score+=80; dropSound = false; break;
        default: break;
    }
    level = max(600 - (score/100) * 35, 100);
}



