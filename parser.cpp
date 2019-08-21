#include <iostream>
#include <vectors>

using namespace std;

int main()
{
	float time;
	int V,k,CC;
	cin>>time>>V>>k;
	vector<string> input(k); 
	for(int i=0;i<k;i++)
	{
		cin>>input[i];
	}
	cin>>CC;
	int MC[V+1][V+1];
	for(int i=0;i<V+1;i++)
	{
		for(int j=0;j<V+1;j++)
		{
			cin>>MC[i][j];
		}
	}
	return 0;

}

