#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

using namespace std;


class Entity
{
    public:
        Entity();

        struct PositionCoords {
            PositionCoords() : x(0), y(0) {}
            int x;
            int y;
        };

        enum Direction {
            AIMLESS = 0,
            NORTH = 1,
            SOUTH = -1,
            EAST = 2,
            WEST = -2
        };

        struct Sight {
            Sight() : direction(AIMLESS), distance(0), object(' ') {}
            Direction direction;
            PositionCoords position;
            int distance;
            char object;
        };
        
        struct Inventory{
            Inventory() : object(' '), total(0) {}
            char object;
            PositionCoords position;
            int total;
        };
        
        const map<char, string> ENTITY_LOOKUP = {
            { 'X', "Wall" },
            { 'C', "Cat" },
            { 'M', "Mouse" },
            { '0', "Cheese" }
        };

        const vector<Direction> cardinals { NORTH, SOUTH, EAST, WEST };

        list<Direction> movement_ops{ NORTH, SOUTH, EAST, WEST };

        Direction direction;
        PositionCoords position;
        Inventory inventory;
        char food;
        char enemy;
        const char WALL = 'X';

        void UpdatePosition(int x, int y);

        virtual vector<vector<char>> ExecuteTurn(vector<vector<char>> board) { return board; };
        virtual Sight LookingPhase(vector<vector<char>> board, Sight sight = Sight()) { return sight; };
        virtual vector<vector<char>> ReactionPhase(vector<vector<char>> board, Sight sight = Sight()) { return board; };

        //look in a specific direction at a position, and return what was seen
        Sight LookDirection(Direction direction, PositionCoords position, vector<vector<char>> board);
        bool IsImportantObject(char object);

        //moves the entity based off the current direction.
        vector<vector<char>> MoveEntity(vector<vector<char>> board);
        //handles logic for swapping spaces in a board during movement.
        vector<vector<char>> MovementBoardSwap(vector<vector<char>> board, int x, int y);

        void RenewMovementOptions();
        Direction RandomDirection();
        string TranslateDirection(Direction direction);
        void BlockDirection(Sight sight);
};

