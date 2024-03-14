#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>      
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "GameBoard.h"
using namespace std;

void GameIteration(GameBoard* g_board)
{
    g_board->IterateSimulation();
    g_board->PrintBoard();
    std::cout << "press ENTER to continue \n";
    char answer = cin.get();
    
}

int main()
{
    GameBoard* new_board = new GameBoard();
    std::cout << "press ENTER to continue \n";
    char answer = cin.get();

    while (answer != 'x')
    {   
        GameIteration(new_board);
    }
    

    return 0;
}