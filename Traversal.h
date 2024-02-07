
#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void InitGameBoard(vector<vector<char>> gBoard);		
char LookSpecificDirection(int x, int y, int dir);		//looks in a specific direction
bool GetPosition(vector<vector<char>> gBoard);			
bool IsInterestingObject(char item);					//determines if an object being looked at is a cat, cheese, or mouse.
bool MoveActor(int x, int y, int dir);					//swaps the Char with a "_"
void GrabObject(int x, int y, char obj);				//replaces an object with a "_".
int GetShortestPathways(int x, int y, int exclusion);	//looks down each hall, and finds the one with the shortest distance

bool CanMove(int x, int y, int dir);					//determines if there is a wall in the way of a character or not.

void PrintCurrTempMap();
vector<vector<char>> UpdateMap();						

#endif
class Traversal
{

	
};