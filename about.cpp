#include "about.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> About::getHighClassic()
{
    fileClassic.open("About/High Score.txt", ios::in);
    int temp;
    while(!fileClassic.eof())
    {
        fileClassic>>temp;
        classicHigh.push_back(temp);
    }
    sort(classicHigh.begin(), classicHigh.end());
    return classicHigh;
}

vector<int> About::getHighBlind()
{
    fileBlind.open("About/Blind High Score.txt", ios::in);
    int temp;
    while(!fileBlind.eof())
    {
        fileBlind>>temp;
        blindHigh.push_back(temp);
    }
    sort(blindHigh.begin(), blindHigh.end());
    return blindHigh;
}

void About::resetHighClassic(int score)
{
    classicHigh.push_back(score);
    ofFileClassic.open("About/High Score.txt", ios::app);
    sort(classicHigh.begin(), classicHigh.end());
    ofFileClassic<<endl<<score;
}

void About::resetHighBlind(int score)
{
    blindHigh.push_back(score);
    ofFileBlind.open("About/Blind High Score.txt", ios::app);
    sort(blindHigh.begin(), blindHigh.end());
    ofFileBlind<<endl<<score;
}

void About::quit()
{
    fileClassic.close();
    fileBlind.close();
    ofFileClassic.close();
    ofFileBlind.close();
}
