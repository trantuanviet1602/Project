#include "menu.hpp"
#include <iostream>
using namespace std;
bool Menu::initialize(const char* title)
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


void Menu::initializeMenu()
{
    loadSurf = IMG_Load("images/menu.png");
    menuTexture = SDL_CreateTextureFromSurface(renderer, loadSurf);
    SDL_FreeSurface(loadSurf);
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    font = TTF_OpenFont("fonts/font.ttf", 30);
}

void Menu::write()
{
    std::string classic = "Classic";
    std::string blindfolded = "Blindfolded";
    std::string quit = "Quit";
    classicTexture = SDL_CreateTextureFromSurface(renderer,(playerChoices==0) ? TTF_RenderText_Blended(font,classic.c_str(),YELLOW) : TTF_RenderText_Blended(font, classic.c_str(),WHITE));
    blindTexture = SDL_CreateTextureFromSurface(renderer,(playerChoices==1) ? TTF_RenderText_Blended(font,blindfolded.c_str(),YELLOW) : TTF_RenderText_Blended(font, blindfolded.c_str(),WHITE));
    quitTexture = SDL_CreateTextureFromSurface(renderer, (playerChoices==2) ? TTF_RenderText_Blended(font, quit.c_str(),YELLOW) : TTF_RenderText_Blended(font, quit.c_str(),WHITE));
    TTF_SizeText(font, classic.c_str(), &classicR.w, &classicR.h);
    TTF_SizeText(font, blindfolded.c_str(), &blindR.w, &blindR.h);
    TTF_SizeText(font, quit.c_str(), &quitR.w, &quitR.h);
    classicR.x = 0 ; classicR.y = 0;
    blindR.x = 0; blindR.y =0;
    quitR.x = 0; quitR.y = 0;

    desClassicR.x = 100;
    desClassicR.y = 250;
    desClassicR.w = classicR.w;
    desClassicR.h = classicR.h;

    desBlindR.x = 100;
    desBlindR.y = 325;
    desBlindR.w = blindR.w;
    desBlindR.h = blindR.h;

    desQuitR.x = 100;
    desQuitR.y = 400;
    desQuitR.w = quitR.w;
    desQuitR.h = quitR.h;

    written = true;
}

void Menu::menu()
{
    SDL_GetTicks();
    handleEvent();
    if(written == false) write();
    updateRender();
}

void Menu::handleEvent()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT: running = false; break;
            case SDL_KEYDOWN:
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP: playerChoices = (playerChoices + 2)% 3 ; written = false; break;
                    case SDLK_DOWN: playerChoices = (playerChoices + 1)%3; written = false; break;
                    case SDLK_RETURN:  //enter
                    {
                        if(playerChoices == 2)
                        {
                            running = false;
                        }
                        else if(playerChoices == 0)
                        {
                            runningGame = true;
                            running = false;
                        }
                        else
                        {
                            runningBlindGame = true;
                            running = false;
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

void Menu::updateRender()
{
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderCopy(renderer, classicTexture, &classicR, &desClassicR);
    SDL_RenderCopy(renderer, blindTexture, &blindR, &desBlindR);
    SDL_RenderCopy(renderer, quitTexture, &quitR, &desQuitR);
    SDL_RenderPresent(renderer);
}

void Menu::quit()
{
    TTF_Quit();
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(classicTexture);
    SDL_DestroyTexture(blindTexture);
    SDL_DestroyTexture(quitTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
