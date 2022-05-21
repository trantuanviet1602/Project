#include "gameover.hpp"
#include <iostream>
using namespace std;

bool GameOver::initialize(const char* title)
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
    running = true;
    return true;
}

void GameOver::write()
{
    std::string restart = "Restart";
    std::string backstr = "Quit";
    std::string mainstr = "Main Menu";
    restartTexture = SDL_CreateTextureFromSurface(renderer,(playerChoices==0) ? TTF_RenderText_Blended(font,restart.c_str(),YELLOW) : TTF_RenderText_Blended(font, restart.c_str(),WHITE));
    mainTexture = SDL_CreateTextureFromSurface(renderer, (playerChoices==1) ? TTF_RenderText_Blended(font,mainstr.c_str(),YELLOW) : TTF_RenderText_Blended(font, mainstr.c_str(),WHITE));
    backTexture = SDL_CreateTextureFromSurface(renderer, (playerChoices==2) ? TTF_RenderText_Blended(font, backstr.c_str(),YELLOW) : TTF_RenderText_Blended(font, backstr.c_str(),WHITE));
    TTF_SizeText(font, restart.c_str(), &restartGameR.w, &restartGameR.h);
    TTF_SizeText(font, mainstr.c_str(), &mainR.w, &mainR.h);
    TTF_SizeText(font, backstr.c_str(), &backR.w, &backR.h);


    restartGameR.x = 0 ; restartGameR.y = 0;
    backR.x = 0; backR.y = 0;

    desRestartGameR.x = 100;
    desRestartGameR.y = 250;
    desRestartGameR.w = restartGameR.w;
    desRestartGameR.h = restartGameR.h;

    desMainR.x = 100;
    desMainR.y = 325;
    desMainR.w = mainR.w;
    desMainR.h = mainR.h;

    desbackR.x = 100;
    desbackR.y = 400;
    desbackR.w = backR.w;
    desbackR.h = backR.h;

    written = true;
}

void GameOver::gameOver()
{
    SDL_GetTicks();
    handleEvent();
    if(written == false) write();
    updateRender();
}

void GameOver::updateRender()
{
    SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
    SDL_RenderCopy(renderer, restartTexture, &restartGameR, &desRestartGameR);
    SDL_RenderCopy(renderer, mainTexture, &mainR, &desMainR);
    SDL_RenderCopy(renderer, backTexture, &backR, &desbackR);
    SDL_RenderPresent(renderer);
}

void GameOver::handleEvent()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT: running = false; runningGame = false; cfquit = true; break;
            case SDL_KEYDOWN:
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP: playerChoices = (playerChoices + 2) % 3; written = false; break;
                    case SDLK_DOWN: playerChoices = (playerChoices + 1) % 3; written = false; break;
                    case SDLK_RETURN:  //enter
                    {
                        if(playerChoices == 2)
                        {
                            runningGame = false;
                            running = false;
                        }
                        else if(playerChoices == 0)
                        {
                            runningGame = true;
                            running = false;
                        }
                        else
                        {
                            running = false;
                            menuRunning = true;
                        }
                        break;
                    }
                    default: break;
                }
            }
            default: break;
        }
    }
}

void GameOver::initializeScreen()
{
    loadSurf = IMG_Load("images/menu.png");
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);
    SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    font = TTF_OpenFont("fonts/font.ttf", 30);
}


void GameOver::quit()
{
    TTF_Quit();
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(restartTexture);
    SDL_DestroyTexture(backTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
