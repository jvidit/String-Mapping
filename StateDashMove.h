#ifndef STATEDASHMOVE_H
#define STATEDASHMOVE_H

#include <map>
#include <utility> 
#include <vector>
#include <cstring>

using namespace std;

class StateDashMove
{

	vector<string> v;
	int cost;
	pair<int, int> next; 
	int difference;

	int costArr[30][30];
	map<char, int> charIndex;

	int calculateCost(int stringIndex,int charIndex);
	void generateNeighbours();
	void mutateState();

public:

	StateDashMove();
	

};

#endif
