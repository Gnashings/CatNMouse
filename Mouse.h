#pragma once
#include "Entity.h"

class Mouse : public Entity
{
	private:
		enum RatMood {
			EXPLORING = 1,      //looks around in every direction, picks a direction, then moves.
			APPROACHING = 2,    //looks only in current direction, and moves only in that direction of a target.
			FLEEING = 3         //looks around in every direction, and flees in the opposite direction of a target.
		};                      //anytime rat looks around, it may choose to change it's behavior depending on what it sees.
		RatMood mood;

		Sight LookingPhase(vector<vector<char>> board, Sight sight = Sight());
		vector<vector<char>> ReactionPhase(vector<vector<char>> board, Sight sight = Sight());
		void DeterminePath(Sight sight);

	public:
		Mouse();
		vector<vector<char>> ExecuteTurn(vector<vector<char>> board);

};

