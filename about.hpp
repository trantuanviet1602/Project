#pragma once
#ifndef ABOUT_H_
#define ABOUT_H_
#include <vector>
#include <fstream>
using namespace std;
class About
{
private:
    vector<int> classicHigh;
    vector<int> blindHigh;
    ifstream fileClassic;
    ifstream fileBlind;
    ofstream ofFileClassic;
    ofstream ofFileBlind;
public:
    vector<int> getHighClassic();
    vector<int> getHighBlind();
    void resetHighClassic(int score);
    void resetHighBlind(int score);
    void quit();
};
#endif // ABOUT_H_
