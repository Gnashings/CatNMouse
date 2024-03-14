#include "Cat.h"

Cat::Cat()
{
	direction = RandomDirection();
	food = 'M';
	mood = WANDERING;
}

vector<vector<char>> Cat::ExecuteTurn(vector<vector<char>> board)
{
	RenewMovementOptions();
	Sight sight;
	sight = LookingPhase(board, sight);
	board = ReactionPhase(board, sight);
	board = MoveEntity(board);
	return board;
}

Cat::Sight Cat::LookingPhase(vector<vector<char>> board, Sight sight)
{
	Sight tempsight;
	switch (mood)
	{
	case Cat::WANDERING:
		//the cat looks around in all directions
		cout << "The Cat saw nothing of interest" << "\n";
		for (Direction dir : cardinals)
		{
			//finding viable paths
			DeterminePath(LookDirection(dir, position, board));
		}
		break;
	case Cat::STALKING:
		//cat looks just in front of them.
		cout << "The Cat tried to look for the Mouse" << "\n";
		sight = LookDirection(direction, position, board);
		DeterminePath(sight);
		if (sight.object != food)
		{
			mood = WANDERING;
		}
		break;
	default:
		break;
	}
	return sight;
}

vector<vector<char>> Cat::ReactionPhase(vector<vector<char>> board, Sight sight)
{
	switch (mood)
	{
	case Cat::WANDERING:
		cout << "The Cat wandered around moving ";
		//removes the ability to walk backwards if there are other options
		if (movement_ops.size() > 1)
		{
			BlockDirection();
			direction = RandomDirection();
		}
		else
			direction = RandomDirection();
		break;
	case Cat::STALKING:
		if (sight.object == food)
		{
			cout << "The Cat stalked the Mouse pursuing it to the ";
			mood = WANDERING;
		}
		break;
	}
	return board;
}

void Cat::DeterminePath(Sight sight)
{
	//if a close wall is detected, remove that option.
	if (sight.distance == 1 && sight.object == WALL)
	{
		BlockDirection(sight);
		return;
	}
	if (sight.distance == 1 && sight.object != food)
	{
		BlockDirection(sight);
		return;
	}

	if (sight.object == food)
	{
		cout << "The Cat spotted a Mouse!" << "\n";
		direction = sight.direction;
		mood = STALKING;
		return;
	}
}
