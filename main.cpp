
#include "graphic.hpp"
#include <iostream>
#include <ctime>
#include "menu.hpp"
#include "gameover.hpp"
#include "audio.hpp"
#include <fstream>
#include <vector>
#include "about.hpp"
#include <algorithm>
using namespace std;
int main(int argc, char* argv[])
{
    About about;
    vector<int> highScoreBlind = about.getHighBlind();
    vector <int> highScore = about.getHighClassic();
    int scoreTemp[5];
    int scoreBlindTemp[5];
    for(int i=0;i<5;i++)
    {
        scoreTemp[i]=highScore[highScore.size()-1-i];
        scoreBlindTemp[i]=highScoreBlind[highScoreBlind.size()-1-i];
    }
    srand(time(NULL));
    Audio audio;
    if(SDL_Init(SDL_INIT_AUDIO)<0) return -2;
    if(audio.initialize()) audio.initializeAudio();
    while(true)
    {

        Menu menu;

        bool runMenu = true;

        if(menu.initialize("Menu"))
        {
            menu.initializeMenu();
            audio.playMenuMusic();
            while(menu.isRunning()) menu.menu();
        }
        Mix_PauseMusic();
        menu.quit();
        if((!menu.isRunning()&&!menu.runGame())&&!menu.runBlindGame())
        {
            return -1;
            break;
        }
        else
        {
            while(true)
            {
                audio.playGameMusic();
                Graphic graphic;
                if(graphic.initialize("Tetris", menu.runBlindGame()))
                {
                    if(menu.runBlindGame()) graphic.initializeGame(scoreBlindTemp);
                    else graphic.initializeGame(scoreTemp);
                    while(graphic.isrunning()&&!graphic.quit())
                    {
                        if(!graphic.nextLevelSound) audio.playNextLvEffect();
                        if(!graphic.playDropSound()) audio.playDropEffect();
                        graphic.play();
                        if(graphic.isPaused()) audio.pause();
                        else audio.resume();
                    }
                    if(!menu.runBlindGame()) about.resetHighClassic(graphic.getScore());
                    else about.resetHighBlind(graphic.getScore());
                    audio.pause();
                    graphic.clean();
                    if(!graphic.quit())
                    {
                        audio.playGameOverEffect();
                        GameOver gameover;
                        if(gameover.initialize("Game Over"))
                        {
                            gameover.initializeScreen();
                            while(gameover.isRunning())
                            {
                                gameover.gameOver();
                            }
                            audio.pause();
                            gameover.quit();
                            if(!gameover.runGame())
                            {
                                if(!gameover.runMenu()||gameover.confirmQuit())
                                {
                                    runMenu = false;
                                    break;
                                }
                            }
                            else continue;
                        }
                    }
                    else
                    {
                        runMenu = false;
                        break;
                    }

                }
                break;
            }

        }
        if(runMenu == false)  break;
    }
    SDL_Quit();
    audio.quit();
    about.quit();
    return 0;
}
