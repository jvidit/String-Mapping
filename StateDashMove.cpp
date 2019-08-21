#include "StateDashMove.h"


StateDashMove::StateDashMove(vector<string> v,int cost,int costArr[][30],map<int, int> charIndex)
{
	this.v=v;
	this.cost=cost;
	this.next = make_pair(-1,-1);
	this.difference = 0;

	this.costArr=costArr;
	this.charIndex=charIndex;
}


StateDashMove::calculateCost(int stringIndex, int charIndex)
{
	int k = v.size();
	int oldCost = 0, newCost = 0;

	for(int i=0;i<k;i++)
	{
		if(i!=stringIndex)
		{
			oldCost+=costArr[v[stringIndex][charIndex]][v[i][charIndex]];
			oldCost+=costArr[v[stringIndex][charIndex-1]][v[i][charIndex-1]];

			newCost+=costArr[v[stringIndex][charIndex]][v[i][charIndex-1]];
			newCost+=costArr[v[stringIndex][charIndex-1]][v[i][charIndex]];
		}
	}
	return newCost-oldCost;
}

StateDashMove::generateNeighbours()
{
	int k = v.size(),n = v[0].size();

	for(int i=0;i<k;i++)
	{
		for(int j=1;j<n;j++)
		{
			if(v[i][j]=='-' && v[i][j-1]!='-')
			{
				int temp = calculateCost(i,j);
				if(difference>temp)
				{
					difference = temp;
					next.first = i;
					next.second = j;
				}
			}
		}
	}
}



StateDashMove::mutateState()
{
	generateNeighbours();
	if(next.fi==-1)
		return;
	char temp = v[next.fi][next.second];
	v[next.fi][next.second]=v[next.fi][next.second-1];
	v[next.fi][next.second-1]=temp;
	difference=0;
}

