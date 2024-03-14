#pragma once

#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Cat.h"
#include "Mouse.h"
#include <functional>
#include <memory>
#ifndef GAMEBOARD_H
#define GAMEBOARD_H
using namespace std;
#endif
/// <summary>
/// Handles game board logic and initalization
/// </summary>

class GameBoard
{
        
    private:
        const int MAX_ROWS = 16;
        const int MAX_COLS = 16;
        vector<vector<char>> gBoard;

        //board functions
        bool IsUsableBoard(vector<vector<char>> board);
        vector<vector<char>> InitalizeBoard(vector<vector<char>> board);
        vector<vector<char>> UpdateBoard(vector<vector<char>> board);

        //entities
        vector<Mouse*> mice;
        vector<Cat*> cats;

    public:
        GameBoard();


        void IterateSimulation();
        void PrintBoard();
        bool badBoard;
};