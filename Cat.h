#pragma once
#include "Entity.h"

class Cat : public Entity
{
    private:
        enum CatMood {
            WANDERING = 1,      //looks around in every direction, picks a direction, then moves.
            STALKING = 2,       //looks only in current direction, and moves only in that direction of a target.
        };                      //anytime cat looks around, it may choose to change it's behavior depending on what it sees.

        CatMood mood;

        Sight LookingPhase(vector<vector<char>> board, Sight sight = Sight());
        vector<vector<char>> ReactionPhase(vector<vector<char>> board, Sight sight = Sight());
        void DeterminePath(Sight sight);

    public:
        Cat();
        vector<vector<char>> ExecuteTurn(vector<vector<char>> board);
};

