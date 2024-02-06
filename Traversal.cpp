#include "Traversal.h"
#include <iostream>

vector<vector<char>> tempBoard;

void InitGameBoard(vector<vector<char>> gBoard)
{
    tempBoard = gBoard;
}

char LookSpecificDirection(int x, int y, int dir)
{
    switch (dir)
    {
    case 1:
        //cout << "looking north" << "\n";
        for (int i = x - 1; i >= 0; i--)
        {
            if (IsInterestingObject(tempBoard[i][y]))
            {
                return tempBoard[i][y];
            }
        }
        //cout << "\n";
        //cout << "\n";
        break;
    case -1:
        cout << "looking south" << "\n";
        for (int i = x + 1; i < tempBoard.size(); i++)
        {
            if (IsInterestingObject(tempBoard[i][y]))
            {
                //swap(gBoard[x - 1][y], gBoard[x][y]);
                return tempBoard[i][y];
            }
        }
        //cout << "\n";
        //cout << "\n";
        break;
    case 2:
        cout << "looking east" << "\n";
        for (int i = y + 1; i < tempBoard.size(); i++)
        {
            if (IsInterestingObject(tempBoard[x][i]))
            {
                return tempBoard[x][i];
            }
        }
        //cout << "\n";
        //cout << "\n";
        break;
    case -2:
        cout << "looking west" << "\n";
        for (int i = y - 1; i >= 1; i--)
        {
            if (IsInterestingObject(tempBoard[x][i]))
            {
                return tempBoard[x][i];
            }
        }
        //cout << "\n";
        //cout << "\n";
        break;
    default:
        break;
    }
}

bool GetPosition(vector<vector<char>> gBoard)
{

    return false;
}

bool IsInterestingObject(char item)
{
    
    if (item == 'X')
    {
        //cout << item << " Nothing of interest was discovered" << "\n";
        return true;
    }
    if (item == '0')
    {
        cout << item << " Cheese was discovered" << "\n";
        return true;
    }
    if (item == '2')
    {
        cout << item << " Cat was discovered" << "\n";
        return true;
    }
    if (item == '1')
    {
        cout << item << " Rat was discovered" << "\n";
        return true;
    }
    //cout << item << " Nothing of interest was discovered" << "\n";
    return false;
}

bool MoveActor(int x, int y, int dir)
{
    vector<vector<char>> bufferBoard;
    int prevMovementx = 0;
    int prevMovementy = 0;
    bool moved = false;
    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            //keeps movement in cardinal direction
            if (abs(j) != abs(i))
            {
                if (tempBoard[x + i][y + j] == '_')
                {
                    //try to move
                    prevMovementx = i;
                    prevMovementy = j;
                    switch (dir)
                    {
                    case 1:
                        if (i == -1 && j == 0)
                        {
                            //cout << "TRYIN NORTH" << "\n";
                            swap(tempBoard[x + i][y + j], tempBoard[x][y]);
                            moved = true;
                        }
                        break;
                    case -1:
                        if (i == 1 && j == 0)
                        {
                            //cout << "TRYIN SOUTH" << "\n";
                            swap(tempBoard[x + i][y + j], tempBoard[x][y]);
                            moved = true;
                        }
                        break;
                    case 2:
                        if (i == 0 && j == 1)
                        {   //cout << "TRYIN EAST" << "\n";
                            swap(tempBoard[x + i][y + j], tempBoard[x][y]);
                            moved = true;
                        }
                        break;
                    case -2:
                        if (i == 0 && j == -1)
                        {   
                            //cout << "TRYIN WEST" << "\n";
                            swap(tempBoard[x + i][y + j], tempBoard[x][y]);
                            moved = true;
                        }
                        break;
                    }
                    //cout << tempBoard[x + i][y + j] << " at i:" << i << " j:" << j << "\n";
                }
                //cout << tempBoard[x + i][y + j] << " at i:" << i << " j:" << j << "\n";
            }
        }
    }

    PrintCurrTempMap();
    return moved;
}

void GrabObject(int x, int y, char obj)
{
    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            //keeps movement in cardinal direction
            if (abs(j) != abs(i))
            {
                if (tempBoard[x + i][y + j] == obj)
                {

                    tempBoard[x + i][y + j] = '_';
                    break;

                }
            }
        }
    }
}

int GetShortestPathways(int x, int y, int exclusion)
{
    int min = 2;
    int direction = 0;
        //north
        for (int i = x - 1; i >= 0; i--)
        {

            if (min >= i)
            {
                if (i >= 2)
                {
                    min = i;
                }
                if (1 != exclusion)
                {
                    direction = 1;
                }
            }

        }
        //cout << "curr min : " << min << "\n";

        for (int i = x + 1; i < tempBoard.size(); i++)
        {
            if (min >= i)
            {
                if (i >= 2)
                {
                    min = i;
                }
                if (-1 != exclusion)
                    direction = -1;
            }
        }
        //cout << "curr min : " << min << "\n";

        for (int i = y + 1; i < tempBoard.size(); i++)
        {
            if (min >= i)
            {
                if (i >= 2)
                {
                    min = i;
                }
                if (2 != exclusion)
                    direction = 2;
            }
        }
        //cout << "curr min : " << min << "\n";

        for (int i = y - 1; i >= 1; i--)
        {
            if (min >= i)
            {
                if (i >= 2)
                {
                    min = i;
                }
                if (-2 != exclusion)
                    direction = -2;
            }
        }
        //cout << "curr min : " << min << "\n";
        return direction;
}

bool CanMove(int x, int y, int dir)
{
    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            //keeps movement in cardinal direction
            if (abs(j) != abs(i))
            {
                if (tempBoard[x + i][y + j] == '_')
                {
                    switch (dir)
                    {
                    case 1:
                        if (i == -1 && j == 0)
                        {
                            //cout << "LOOKIN NORTH" << "\n";
                            return true;
                        }
                        break;
                    case -1:
                        if (i == 1 && j == 0)
                        {
                            //cout << "LOOKIN SOUTH" << "\n";
                            return true;
                        }
                        break;
                    case 2:
                        if (i == 0 && j == 1)
                        {
                            //cout << "LOOKIN EAST" << "\n";
                            return true;
                        }
                        break;
                    case -2:
                        if (i == 0 && j == -1)
                        {
                            //cout << "LOOKIN WEST" << "\n";
                            return true;
                        }
                        break;
                    }
                }
            }
        }
    }
    return false;
}

void PrintCurrTempMap()
{
    if (tempBoard.empty() == false)
    {
        for (int i = 0; i < tempBoard.size(); i++) {
            for (int j = 0; j < tempBoard[i].size(); j++) {
                if (j == 0)
                    cout << tempBoard[i][j] << " ";
                else
                    cout << tempBoard[i][j] << " ";
                if (j == 15)
                {
                    cout << "\n";
                }
            }
        }
    }
}

vector<vector<char>> UpdateMap()
{

    return tempBoard;
}