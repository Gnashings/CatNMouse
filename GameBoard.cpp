#include "GameBoard.h"
#include <vector>
#include <iostream>
#include <functional>



GameBoard::GameBoard()
{
    if (IsUsableBoard(gBoard) == true)
    {
        gBoard = InitalizeBoard(gBoard);
        PrintBoard();
    }
    
}

bool GameBoard::IsUsableBoard(vector<vector<char>> board)
{
    ifstream lvl_map("LevelMap.txt");

    if (lvl_map.is_open())
    {
        std::string line;
        while (std::getline(lvl_map, line))
        {
            vector<char> row;
            for (char& c : line)
            {
                row.push_back(c);
            }
            board.push_back(row);
            //row check
            if (row.size() != MAX_ROWS)
            {
                cout << "Row size at :" << row.size() << " is not equal to " << MAX_ROWS << " \n";
                return false;
            }
        }
        //column check
        if (MAX_COLS != board.size())
        {
            cout << "Column size at : " << board.size() << " is not equal to " << MAX_COLS << " \n";
            return false;
        }

        //top wall check
        for (int i = 0; i < board[0].size(); i++)
        {
            if (board[0][i] != 'X')
            {
                cout << "Top walls are missing";
                return false;
            }
        }
        //bot wall check
        for (int i = 0; i < board[MAX_ROWS -1].size(); i++)
        {
            if (board[MAX_ROWS - 1][i] != 'X')
            {
                cout << "Bottom walls are missing";
                return false;
            }
        }
        //left wall check
        for (int i = 0; i < board.size(); i++) {

            if (board[i][0] != 'X')
            {
                cout << "Left walls are missing";
                return false;
            }
        }
        //right wall check
        for (int i = 0; i < board[MAX_COLS - 1].size(); i++) {

            if (board[i][MAX_COLS - 1] != 'X')
            {
                cout << "Right walls are missing";
                return false;
            }
        }
    }

    gBoard = board;
    return true;

}


void GameBoard::IterateSimulation()
{
    if (mice.size() != 0)
    {
        for(Mouse* m : mice)
        {
            gBoard = m->ExecuteTurn(gBoard);
        }
    }
    if (cats.size() != 0)
    {
        for (Cat* c : cats)
        {
            gBoard = c->ExecuteTurn(gBoard);
        }
    }
    
}

vector<vector<char>> GameBoard::InitalizeBoard(vector<vector<char>> board)
{
    cout << "Loading map:" << "\n";
    for (int i = 0; i < board.size(); i++) {

        for (int j = 0; j < board[i].size(); j++)
        {
            switch (board[i][j])
            {
            case 'M':
            {
                Mouse* mouse = new Mouse{};
                mouse->UpdatePosition(i, j);
                mice.push_back(mouse);
                cout << "Mouse discovered \n";
            }
            break;
            case 'C':
            {
                Cat* cat = new Cat{};
                cat->UpdatePosition(i, j);
                cats.push_back(cat);
                cout << "Cat discovered \n";
            }
            break;
            case '0':
                cout << "Cheese discovered \n";
                break;
            case '_':
                break;
            case 'X':
                break;
            default:
                cout << "Unidentified entity [" << board[i][j] << "] converting to wall [X]\n";
                board[i][j] = 'X';
                break;
            }
        }
    }
    return board;
}

vector<vector<char>> GameBoard::UpdateBoard(vector<vector<char>> board)
{
    return board;
}


void GameBoard::PrintBoard()
{   
    //swaps the underscore, and spaces out characters to improve visuals
    if (gBoard.empty() == false)
    {
        for (int i = 0; i < gBoard.size(); i++) {
            for (int j = 0; j < gBoard[i].size(); j++) {
                if (gBoard[i][j] == '_')
                {
                    cout << " " << "";
                }
                else
                {
                    cout << gBoard[i][j] << "";
                }
                if (j == gBoard.size()-1)
                {
                    cout << "\n";
                }
            }
        }
    }
}

