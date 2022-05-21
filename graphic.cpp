#include <iostream>
#include "graphic.hpp"
using namespace std;

//initialization

bool Graphic::initialize(const char* title, bool blindfolded)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
		if (window != NULL)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer != NULL)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				int imgFlags = IMG_INIT_PNG;
				int initted = IMG_Init(imgFlags);
				if ((initted & imgFlags) != imgFlags)   cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;

			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
    if(TTF_Init()<0) return false;
    game_.running = true;
    blindFolded = blindfolded;
	return true;
}

void Graphic::initializeGame(int scoreTemp[])
{
    for(int i=0;i<5;i++)
    {
        highScore[i] = scoreTemp[i];
    }

    SDL_Surface* loadSurf = IMG_Load("images/background(1).png");
    background = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);


    loadSurf = IMG_Load("images/blocks.png");
    blocks = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("image/blind.png");
    blindBlocks = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);


    loadSurf=IMG_Load("images/predictionblocks.png");
    predictionBlocks = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);

    loadSurf = IMG_Load("images/pause.png");
    pauseBackground = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);

    font = TTF_OpenFont("fonts/font.ttf", 15);
}






//setup graphic.
void Graphic::write()
{
    stringstream highScorestr;
    if(game_.score < highScore[0])
    {
        highScorestr<<"Next High Score:";
        if(game_.score > highScore[1]) highScorestr<<highScore[0];
        else if(game_.score > highScore[2]) highScorestr<<highScore[1];
        else if(game_.score > highScore[3]) highScorestr<<highScore[2];
        else if(game_.score > highScore[4]) highScorestr<<highScore[3];
        else highScorestr<<highScore[4];
    }
    else highScorestr<<"New Best Score!";
    string s = highScorestr.str();
    highScoreTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(font, s.c_str(), WHITE));
    TTF_SizeText(font, s.c_str(), &highR.w, &highR.h);
    highR.x = 0;
    highR.y = 0;
    desHighR.h = highR.h;
    desHighR.w = highR.w;
    desHighR.x = 30; desHighR.y = 90;


    stringstream levelstr;
    if(game_.level<currentLevel)
    {
        nextLevelSound = false;
        currentLevel = game_.level;
    }
    if(game_.level>100)
    {
        int index = game_.score /100 + 1 ;
        levelstr<<"Level "<<index;
    }
    else levelstr<<"Level MAX!";
    s = levelstr.str();
    levelTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(font, s.c_str(), WHITE));
    TTF_SizeText(font, s.c_str(), &levelR.w, &levelR.h);
    levelR.x = 0; levelR.y = 0;
    desLevelR.x = 290; desLevelR.y = 530;
    desLevelR.w = levelR.w;
    desLevelR.h = levelR.h;

    stringstream strm ;
    strm<<game_.score;
    s = strm.str();

    scoreTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(font, s.c_str(),WHITE));

    TTF_SizeText(font, s.c_str(), &writeR.w, &writeR.h);

    writeR.x=0; writeR.y = 0;
    desWriteR.x = 320 ; desWriteR.y = 500;
    desWriteR.w = writeR.w;
    desWriteR.h = writeR.h;

    game_.written=1;
}


void Graphic::play()
{
    game_.dropSound = true;
    nextLevelSound = true;
    game_.setCurrentTime(SDL_GetTicks());
    game_.handleEvents();
    game_.gameplay();
    if(game_.written==0) write();
    if(!blindFolded) updateRender();
    else updateBlindRender();
}

bool Graphic:: checkForPrediction()
{
    for(int i = 0; i < 4; i++)
    {
        if (game_.predictionItems[i].y < 0) return false;
    }
    return true;
}


void Graphic::updateBlindRender()
{
    if(game_.pausing)
    {
        SDL_RenderCopy(renderer, pauseBackground, NULL, NULL);
    }
    else
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);

        if(game_.items[0].figure!=-1&&checkForPrediction())
        for (int i = 0; i < 4; i++)
        {
            setRectPos(destPredictionR, game_.predictionItems[i].x * BlockW, (game_.predictionItems[i].y) * BlockH);
            moveRectPos(destPredictionR, BlockW, ScreenH - (Lines + 1) * BlockH);
            SDL_RenderCopy(renderer, predictionBlocks, NULL, &destPredictionR);
        }

        for (int i = 0; i < Lines; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                if (game_.field[i][j])
                {
                    setRectPos(srcR, game_.field[i][j] * 0);
                    setRectPos(destR, j * BlockW, i * BlockH);
                    moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
                    SDL_RenderCopy(renderer, blindBlocks, &srcR, &destR);
                }
            }
        }

        if(game_.watch)
        {
            //setup for drawing tetrimino in the field.
            for (int i = 0; i < Lines; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    if (game_.field[i][j])
                    {
                        setRectPos(srcR, game_.field[i][j] * BlockW);
                        setRectPos(destR, j * BlockW, i * BlockH);
                        moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
                        SDL_RenderCopy(renderer, blocks, &srcR, &destR);
                    }
                }
            }
        }


        for (int i = 0; i < 4; i++)
        {
            setRectPos(srcR, game_.items[0].colors * BlockW);
            if(game_.items[i].y>=0)
            {
                setRectPos(destR, game_.items[i].x * BlockW, game_.items[i].y * BlockH);

            }
            moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
            SDL_RenderCopy(renderer, blocks, &srcR, &destR);
        }


        //setup drawing rect for held Tetrimino.
        for (int i = 0; i < 4; i++)
        {
            setRectPos(srcHoldR, game_.holdItems[i].colors * BlockW);
            setRectPos(destHoldR, game_.holdItems[i].x*BlockW, game_.holdItems[i].y*BlockH);
            switch(game_.holdItems[0].figure)
            {

                // Set the suitable position for drawing held Tetromino.
                case 0:     moveRectPos(destHoldR, 222, 330); break;
                case 1:     moveRectPos(destHoldR, 222, 330); break;
                case 2:     moveRectPos(destHoldR, 222, 330); break;
                case 3:     moveRectPos(destHoldR, 210, 340); break;
                case 4:     moveRectPos(destHoldR, 222, 330); break;
                case 5:     moveRectPos(destHoldR, 222, 330); break;
                case 6:     moveRectPos(destHoldR, 210, 340); break;
            }

            SDL_RenderCopy(renderer, blocks, &srcHoldR, &destHoldR);
        }


        //setup drawing rect for next Tetrimino.
            for (int i = 0; i < 4; i++)
        {
            setRectPos(srcNextR, game_.nextItems[i].colors * BlockW);
            setRectPos(destNextR, game_.nextItems[i].x*BlockW, game_.nextItems[i].y*BlockH);
            switch(game_.nextItems[0].figure)
            {

                // Set the suitable position for drawing next Tetromino.
                case 0:     moveRectPos(destNextR, 222, 175); break;
                case 1:     moveRectPos(destNextR, 222, 175); break;
                case 2:     moveRectPos(destNextR, 222, 175); break;
                case 3:     moveRectPos(destNextR, 210, 175); break;
                case 4:     moveRectPos(destNextR, 222, 175); break;
                case 5:     moveRectPos(destNextR, 222, 175); break;
                case 6:     moveRectPos(destNextR, 210, 175); break;
            }

            SDL_RenderCopy(renderer, blocks, &srcNextR, &destNextR);
        }
        SDL_RenderCopy(renderer, highScoreTexture, &highR, &desHighR);
        SDL_RenderCopy(renderer, levelTexture, &levelR, &desLevelR);
        SDL_RenderCopy(renderer, scoreTexture, &writeR, &desWriteR);

        if(game_.gameOver())
        {
            SDL_Delay(300);
            game_.running=false;
        }
    }

	SDL_RenderPresent(renderer);
}



void Graphic::updateRender()
{
    if(game_.pausing)
    {
        SDL_RenderCopy(renderer, pauseBackground, NULL, NULL);
    }
    else
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
        if(game_.items[0].figure!=-1&&checkForPrediction())
        for (int i = 0; i < 4; i++)
        {
            setRectPos(destPredictionR, game_.predictionItems[i].x * BlockW, (game_.predictionItems[i].y) * BlockH);
            moveRectPos(destPredictionR, BlockW, ScreenH - (Lines + 1) * BlockH);
            SDL_RenderCopy(renderer, predictionBlocks, NULL, &destPredictionR);
        }


        //setup for drawing tetrimino in the field.
        for (int i = 0; i < Lines; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                if (game_.field[i][j])
                {
                    setRectPos(srcR, game_.field[i][j] * BlockW);
                    setRectPos(destR, j * BlockW, i * BlockH);
                    moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
                    SDL_RenderCopy(renderer, blocks, &srcR, &destR);
                }
            }
        }


        for (int i = 0; i < 4; i++)
        {
            setRectPos(srcR, game_.items[0].colors * BlockW);
            if(game_.items[i].y>=0)
            {
                setRectPos(destR, game_.items[i].x * BlockW, game_.items[i].y * BlockH);

            }
            moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
            SDL_RenderCopy(renderer, blocks, &srcR, &destR);
        }


        //setup drawing rect for held Tetrimino.
        for (int i = 0; i < 4; i++)
        {
            setRectPos(srcHoldR, game_.holdItems[i].colors * BlockW);
            setRectPos(destHoldR, game_.holdItems[i].x*BlockW, game_.holdItems[i].y*BlockH);
            switch(game_.holdItems[0].figure)
            {

                // Set the suitable position for drawing held Tetromino.
                case 0:     moveRectPos(destHoldR, 222, 330); break;
                case 1:     moveRectPos(destHoldR, 222, 330); break;
                case 2:     moveRectPos(destHoldR, 222, 330); break;
                case 3:     moveRectPos(destHoldR, 210, 340); break;
                case 4:     moveRectPos(destHoldR, 222, 330); break;
                case 5:     moveRectPos(destHoldR, 222, 330); break;
                case 6:     moveRectPos(destHoldR, 210, 340); break;
            }

            SDL_RenderCopy(renderer, blocks, &srcHoldR, &destHoldR);
        }


        //setup drawing rect for next Tetrimino.
            for (int i = 0; i < 4; i++)
        {
            setRectPos(srcNextR, game_.nextItems[i].colors * BlockW);
            setRectPos(destNextR, game_.nextItems[i].x*BlockW, game_.nextItems[i].y*BlockH);
            switch(game_.nextItems[0].figure)
            {

                // Set the suitable position for drawing next Tetromino.
                case 0:     moveRectPos(destNextR, 222, 175); break;
                case 1:     moveRectPos(destNextR, 222, 175); break;
                case 2:     moveRectPos(destNextR, 222, 175); break;
                case 3:     moveRectPos(destNextR, 210, 175); break;
                case 4:     moveRectPos(destNextR, 222, 175); break;
                case 5:     moveRectPos(destNextR, 222, 175); break;
                case 6:     moveRectPos(destNextR, 210, 175); break;
            }

            SDL_RenderCopy(renderer, blocks, &srcNextR, &destNextR);
        }
        SDL_RenderCopy(renderer, highScoreTexture, &highR, &desHighR);
        SDL_RenderCopy(renderer, levelTexture, &levelR, &desLevelR);
        SDL_RenderCopy(renderer, scoreTexture, &writeR, &desWriteR);

        if(game_.gameOver())
        {
            SDL_Delay(300);
            game_.running=false;
        }
    }

	SDL_RenderPresent(renderer);
}

//setup rect position


void Graphic::setRectPos(SDL_Rect& rect, int x, int y, int w, int h)
{
	rect = { x, y, w, h };
}

void Graphic::moveRectPos(SDL_Rect& rect, int x, int y)
{
	rect.x += x;
	rect.y += y;
}



void Graphic::clean()
{
	SDL_DestroyTexture(blocks);
	SDL_DestroyTexture(blindBlocks);
	SDL_DestroyTexture(predictionBlocks);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(pauseBackground);
	SDL_DestroyTexture(highScoreTexture);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(levelTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
}




