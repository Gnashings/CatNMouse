
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Traversal.h"
#include <time.h>      
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>       

enum RatMood {
    EXPLORING = 1,      //looks around in every direction, picks a direction, then moves.
    APPROACHING = 2,    //looks only in current direction, and moves only in that direction of a target.
    FLEEING = 3         //looks around in every direction, and flees in the opposite direction of a target.
};                      //anytime rat looks around, it may choose to change it's behavior depending on what it sees.
RatMood rMood;

enum CatMood {
    WANDERING = 1,      //looks around in every direction, picks a direction, then moves.
    STALKING = 2,       //looks only in current direction, and moves only in that direction of a target.
};                      //anytime cat looks around, it may choose to change it's behavior depending on what it sees.
CatMood cMood;

enum Direction {        //having north/south & east/west be the same number, but negative allows us to flip direction easily.
    AIMLESS = 0,
    NORTH = 1,
    SOUTH = -1,
    EAST = 2,
    WEST = -2
};
Direction ratDir;
Direction catDir;

int ratx = 0;
int raty = 0;

int catx = 0;
int caty = 0;


vector<int> deck{ -2, -1, 1, 2 };       //our possible directions. In number form.
vector<vector<char>> gameBoard;

//sett
int RandomSeed(vector<int> exclude)
{
    //using time to generate a seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    //shuffling that deck
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    vector<int> buffer = deck;

    //all directions that overlap with excluded paths get set to zero
    for (auto& x : exclude)
    {
        for (auto& z : buffer)
        {
            if (x == z)
            {
                //cout << "exlu: " << x << " buff: " << z << "\n";
                z = 0;
            }
        }
    }
    
    //draw the first non-zero, and set to direction
    for (int& y : buffer)
    {
        //cout << "buffer: " << y << "\n";
        if (y != 0)
        {
            return y;
        }
    }
    return 0;
}

void PrintMap(vector<vector<char>> gBoard) {
    for (int i = 0; i < gBoard.size(); i++) {
        for (int j = 0; j < gBoard[i].size(); j++) {
            if (j == 0)
                cout << gBoard[i][j] << " ";
            else
                cout << gBoard[i][j] << " ";
            if (j == 15)
            {
                cout << "\n";
            }
        }
    }
}

//first we look around, depending on our mood
//then we take a movement option, which might have changed based on our mood
void RatTurn()
{
    char object;
    vector<int> exclusions;

    for (int i : {1, -1, 2, -2})
    {
        if (CanMove(ratx, raty, i) == false)
        {
            exclusions.push_back(i);
        }
    }
    switch (rMood) {
    case EXPLORING:
        cout << "RAT: I'm just looking around" << "\n";
        for (int i : {1, -1, 2, -2})
        {
            object = LookSpecificDirection(ratx, raty, i);
            
            if (object == '2')
            {   
                //We saw a cat! Better leave!
                exclusions.push_back(i);
                ratDir = (Direction)-i;
                rMood = FLEEING;
                break;
            }
            if (object == '0')
            {
                //We see cheese, better approach!
                ratDir = (Direction)i;
                //cout << "(APPROACHING)CHANGING DIR TO " << ratDir << "\n";
                rMood = APPROACHING;
            }
        }
        //if our path is blocked
        if (CanMove(ratx, raty, ratDir) == false)
        {
            exclusions.push_back(-ratDir);
            exclusions.push_back(ratDir);
            int seed = RandomSeed(exclusions);
            ratDir = (Direction)seed;
            break;
        }
        if (exclusions.size() <= 1)
        {
            GetShortestPathways(ratx, raty, -ratDir);
        }
        break;
    case APPROACHING:
        cout << "RAT: Ooooh cheese!" << ratDir << "\n";
        GrabObject(ratx, raty, '0');
        object = LookSpecificDirection(ratx, raty, ratDir);
        if (object == '2')
        {
            //We saw a cat! Better leave!
            rMood = FLEEING;
            break;
        }
        if (object != '0')
        {
            rMood = EXPLORING;
        }
        break;
    case FLEEING:
        cout << "RAT: is the cat still behind me?" << "\n";
        for (int i : {1, -1, 2, -2})
        {
            object = LookSpecificDirection(ratx, raty, i);

            if (object == '2')
            {
                //We saw a cat! Better leave!
                cout << "RAT: I saw a cat!";
                exclusions.push_back(i);
                if (CanMove(ratx, raty, ratDir) == false)
                {
                    exclusions.push_back(-ratDir);
                    exclusions.push_back(ratDir);
                    int seed = RandomSeed(exclusions);
                    ratDir = (Direction)seed;
                    break;
                }
                int seed = RandomSeed(exclusions);
                ratDir = (Direction)seed;
                break;
            }
            else
            {
                int seed = RandomSeed(exclusions);
                ratDir = (Direction)seed;
                rMood = EXPLORING;
            }
        }
        GrabObject(ratx, raty, '0');
        break;
    }
    //cout << "CURRENT RAT DIRECTION: " << ratDir << '\n';
    bool hadMoved;
    switch (rMood) {
    case EXPLORING:
        cout << "RAT: exploring around!" << "\n";
        MoveActor(ratx, raty, ratDir);
        GrabObject(ratx, raty, '0');
        break;
    case APPROACHING:
        cout << "RAT: approaching cheese!" << ratDir << "\n";
        MoveActor(ratx, raty, ratDir);
        break;
    case FLEEING:
        cout << "RAT: fleeing away!" << "\n";
        //cout << "FLEE MOVEMENT DIR " << ratDir << "\n";
        MoveActor(ratx, raty, ratDir);
        break;
    }
}

//first we look around, depending on our mood
//then we take a movement option, which might have changed based on our mood
void CatTurn()
{
    if (catx == 0 && caty == 0)
    {
        return;
    }
    char object;
    vector<int> exclusions;
    for (int i : {1, -1, 2, -2})
    {
        if (CanMove(catx, caty, i) == false)
        {
            exclusions.push_back(i);
        }
    }
    switch (cMood) {
    case WANDERING:
        cout << "CAT: looking for that rat..." << "\n";
        if (exclusions.size() == 0)
        {
            exclusions.push_back(catDir);
            int seed = RandomSeed(exclusions);
            catDir = (Direction)seed;
        }
        object = LookSpecificDirection(catx, caty, catDir);
        if (object == '1')
        {
            cout << "CAT: I see a rat!" << "\n";
            //We see a rat, get em!
            cMood = STALKING;
            break;
        }
        //if our path is blocked
        if (CanMove(catx, caty, catDir) == false)
        {
            cout << "Something in my way " << catDir << "\n";
            if (object == '0')
            {
                catDir = (Direction)-catDir;
                break;
            }
            exclusions.push_back(catDir);
            exclusions.push_back(-catDir);
            
            int seed = RandomSeed(exclusions);
            catDir = (Direction)seed;
            break;
        }
        if (exclusions.size() <= 1)
        {
            GetShortestPathways(catx, caty, -catDir);
        }
        //MoveActor(catx, caty, catDir);
        GrabObject(catx, caty, '1');
        break;
    case STALKING:
        cout << "CAT: I see a rat!" << "\n";
        object = LookSpecificDirection(catx, caty, catDir);
        if (object != '1')
        {
            cout << "CAT: I lost the rat!" << "\n";
            cMood = WANDERING;
        }
        //cout << "CAT: STALKING" << catDir << "\n";
        //MoveActor(catx, caty, catDir);
        break;
    }
    
    switch (cMood) {
    case WANDERING:
        cout << "CAT: I wonder where he might be..." << "\n";
        //cout << "CATX CATY CATDIR: " << catx << caty << catDir <<"\n";
        MoveActor(catx, caty, catDir);
        GrabObject(catx, caty, '1');
        break;
    case STALKING:
        cout << "CAT: Running after him!" << "\n";;
        //cout << "STALKING MOVEMENT" << catDir << "\n";
        MoveActor(catx, caty, catDir);
        break;
    }
}

//simply allows us to gather character positions.
void DetermineCharacterPositions()
{
    bool ratAlive = true;

    for (int i = 0; i < gameBoard.size(); i++) {
        for (int j = 0; j < gameBoard[i].size(); j++)
        {
            if (gameBoard[i][j] == '1')
            {
                ratx = i;
                raty = j;
                ratAlive = true;
            }
            if (gameBoard[i][j] == '2')
            {
                catx = i;
                caty = j;
            }
        }
    }
}

void GameIteration() {
    gameBoard = UpdateMap();
    DetermineCharacterPositions();
    RatTurn();
    CatTurn();
    gameBoard = UpdateMap();
    PrintMap(gameBoard);
    cout << "press any character but 'x' and enter to progress the simulation" << "\n";
    char answer;
    std::cin >> answer;
}

int main()
{
    std::ifstream lvlmap("LevelMap.txt");
    int max_rows = 16;
    int max_cols = 16;


    //Board init
    if (lvlmap.is_open())
    {
        std::string line;
        while (std::getline(lvlmap, line))
        {
            vector<char> row;
            for (char& c : line)
            {
                row.push_back(c);
            }
            gameBoard.push_back(row);
        }
        cout << "Printing Raw Map Data..." << "\n";

        for ( int i = 0; i < gameBoard.size(); i++) {
            
            for ( int j = 0; j < gameBoard[i].size(); j++)
            {
                if (gameBoard[i][j] == '1')
                {
                    ratx = i;
                    raty = j;
                }
                cout << gameBoard[i][j];
            }
            cout << "\n";
        }

        cout << "Printing Visual Map..." << "\n";
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {

                if (j == 0)
                    cout << gameBoard[i][j] << " ";
                else
                    cout <<  gameBoard[i][j] << " ";
                if (j == 15)
                {
                    cout << "\n";
                }
            }
        }
    }
    
    //initalsetup
    InitGameBoard(gameBoard);
    gameBoard = UpdateMap();

    //cat n rat setup
    rMood = EXPLORING;
    ratDir = SOUTH;
    cMood = WANDERING;
    catDir = SOUTH;
    
    RatTurn();
    gameBoard = UpdateMap();
    CatTurn();
    gameBoard = UpdateMap();

    //updating positions
    DetermineCharacterPositions();
    cout << "press any character but 'x' and enter to progress the simulation" << "\n";
    char answer;
    std::cin >> answer;
    while (answer != 'x')
    {
        GameIteration();
    }

    return 0;
}