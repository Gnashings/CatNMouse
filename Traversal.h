
#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void InitGameBoard(vector<vector<char>> gBoard);
char LookSpecificDirection(int x, int y, int dir);
bool GetPosition(vector<vector<char>> gBoard);
bool IsInterestingObject(char item);
bool MoveActor(int x, int y, int dir);
void GrabObject(int x, int y, char obj);
int GetShortestPathways(int x, int y, int exclusion);

bool CanMove(int x, int y, int dir);

void PrintCurrTempMap();
vector<vector<char>> UpdateMap();

#endif
class Traversal
{

	
};