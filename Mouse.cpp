#include "Mouse.h"

Mouse::Mouse()
{
	direction = RandomDirection();
	food = '0';
	enemy = 'C';
	mood = EXPLORING;
}

vector<vector<char>> Mouse::ExecuteTurn(vector<vector<char>> board)
{
	RenewMovementOptions();
	Sight sight;
	sight = LookingPhase(board, sight);
	board = ReactionPhase(board, sight);
	board = MoveEntity(board);
	return board;
}

Mouse::Sight Mouse::LookingPhase(vector<vector<char>> board, Sight sight)
{
	Sight tempsight;
	switch (mood)
	{
	case Mouse::EXPLORING:
		//the Mouse looks around in all directions
		cout << "The Mouse looked around" << "\n";
		for (Direction dir : cardinals)
		{
			//finding viable paths
			DeterminePath(LookDirection(dir, position, board));
		}
		break;
	case Mouse::APPROACHING:
		//Mouse looks just in front of them.
		cout << "The Mouse stared at the Cheese" << "\n";
		sight = LookDirection(direction, position, board);
		DeterminePath(sight);
		if (sight.object == enemy)
		{
			//We saw a cat! Better leave!
			mood = FLEEING;
			break;
		}
		if (sight.object != food)
		{
			mood = EXPLORING;
		}
		break;
	case Mouse::FLEEING:
		cout << "The Mouse looked around trying to find the Cat" << "\n";
		bool sawCat;
		sawCat = false;
		for (Direction dir : cardinals)
		{
			//finding viable paths
			sight = (LookDirection(dir, position, board));
			DeterminePath(sight);

			//ensure that if a cat is spotted, immediately flee.
			if (sight.object == enemy)
			{
				sawCat = true;
			}
		}
		if (sawCat == false)
		{
			mood = EXPLORING;
			
		}
		break;
	default:
		break;
	}
	return sight;
}

vector<vector<char>> Mouse::ReactionPhase(vector<vector<char>> board, Sight sight)
{
	switch (mood)
	{
	case Mouse::EXPLORING:
		cout << "The Mouse explored around and moves ";
		//removes the ability to walk backwards if there are other options
		if (movement_ops.size() > 1)
		{
			BlockDirection();
			direction = RandomDirection();
		}
		else
			direction = RandomDirection();
		break;
	case Mouse::APPROACHING:
		if (sight.object == food)
		{
			cout << "The Mouse moves towards the Cheese ";
			mood = EXPLORING;
		}
		break;
	case Mouse::FLEEING:
		cout << "The Mouse fled from the cat moving ";
		direction = RandomDirection();
		break;
	default:
		break;
	}
	//cout << "My last Direction is: "<< TranslateDirection(direction) <<" \n";
	return board;
}

void Mouse::DeterminePath(Sight sight)
{
	//if a close wall is detected, remove that option.
	if (sight.distance == 1 && sight.object != food)
	{
		BlockDirection(sight);
		return;
	}
	//if a cat is detected, remove that direction, and FLEE!
	if (sight.object == enemy)
	{
		cout << "The Mouse saw a cat!\n";
		BlockDirection(sight);
		mood = FLEEING;
		return;
	}
	//if cheese is detected, start approaching.
	if (sight.object == food)
	{
		cout << "The Mouse saw cheese\n";
		//set the direction to the cheese.
		direction = sight.direction;
		mood = APPROACHING;
		return;
	}
}
