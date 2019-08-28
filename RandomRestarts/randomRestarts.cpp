#include <iostream>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <fstream>
#include <queue>
#include <deque>
#include <stdio.h>
#include <map>
#include <random>

using namespace std;

int cost_bound=INT_MAX;
int CC;
map<char,int> charIndex;
int costArr[30][30];   


vector<string> callParser();

//pre-processing, returns number of dashses inserted
int completeDashes(vector<string>&,int);

pair<int,vector<string> > completeDashesRandomized(vector<string>, int);


//gets cost of a state
int calcCost(vector<string>);


//cost calculation for a neighbour
int getDifference(vector<string>, int, int);

//turns input into its nearest neighbour, if possible. returns 1 or 0. 
int minNeighbour(vector<string>&);


void pr(vector<string>);


//void localSearch(vector<string>&);


int main(int argc, char*argv[])
{
	freopen (argv[1],"r",stdin);
    freopen (argv[2],"w",stdout);

    vector<string> dataset=callParser();

    int length = 15;


    for(int i=0;i<5;i++)
    {
    	pair <int,vector<string> > initialState = completeDashesRandomized(dataset, length);
    	int DashInsertionCost = CC*initialState.first;

    	
    }
    return 0;

    int count = 0;

    while(minNeighbour(dataset))
    	count++;

    cout<<count<<endl;

    cout<<calcCost(dataset)+DashInsertionCost<<endl;
    pr(dataset);
    
    // return 0;
}






















void pr(vector<string> v)
{
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<endl;
}




int minNeighbour(vector<string>& v)
{
	int stringIndex=-1, switchIndex = -1, diff = 0,temp;
	for(int i=0;i<v.size();i++)
	{
		for(int j=0;j<v[0].size();j++)
		{
			if(v[i][j]=='-')
			{
				temp = getDifference(v,i,j);
				if(temp<diff)							
				{
					diff = temp;
					stringIndex=i;
					switchIndex=j;					
				}

				temp = getDifference(v,i,j-1);
				if(temp<diff)							//note switch index can be -1, and matters when temp<=diff
				{
					diff = temp;
					stringIndex=i;
					switchIndex=j-1;					
				}

			}
		}
	}

	if(stringIndex!=-1)
	{
		swap(v[stringIndex][switchIndex],v[stringIndex][switchIndex+1]);
		return 1;
	}
	return 0;
	
}




//switch switchIndex and switchIndex+1

int getDifference(vector<string> v, int stringIndex, int switchIndex)
{
	if(switchIndex==-1)
		return 0;

	int diff = 0;

	
	int a1 = charIndex[v[stringIndex][switchIndex]], a2 = charIndex[v[stringIndex][switchIndex+1]];

	for(int i=0;i<v.size();i++)
	{
		int b1 = charIndex[v[i][switchIndex]];
		int b2 = charIndex[v[i][switchIndex+1]];

		int oldCost=costArr[a1][b1]+costArr[a2][b2];
		int newCost=costArr[a2][b1]+costArr[a1][b2];

		diff+=newCost-=oldCost;
	}
	return diff;
}






int completeDashes(vector<string>&v,int length)
{
	int totDashes = 0;
	for(int i=0;i<v.size();i++)
	{
		int deficit = length-v[i].size();
		totDashes+=deficit;
		for(int j=0;j<deficit;j++)
			v[i]+="-";
	}
	return totDashes;
}

pair<int,vector<string> > completeDashesRandomized(vector<string> v, int length)
{
    vector<int> gen;
    for(int i=0;i<length;i++)
        gen.push_back(i);
    
    int totDashes=0;
    
    for(int i=0;i<v.size();i++)
    {
        int deficit = length-v[i].size();
        totDashes+=deficit;
        
        random_shuffle(gen.begin(),gen.end());
        sort(gen.begin(),gen.begin()+deficit);
        
        int ind1=0,ind2=0;
        string s="";
        while(ind1+ind2<length)
        {
            if(ind1+ind2==gen[ind2])
            {
                s+="-";
                ind2++;
            }
            else
            {
                s+=v[i][ind1];
                ind1++;
            }
        }
        v[i]=s;
        
    }
    return make_pair(totDashes,v);
}






int calcCost(vector<string> v)
{
	int tot = 0;
	
	for(int i=0;i<v.size();i++)
	{
		for(int j = i+1;j<v.size();j++)
		{
			for(int k = 0;k<v[0].size();k++)
			{
				int a = charIndex[v[i][k]];
				int b = charIndex[v[j][k]];

				tot+=costArr[a][b];
			}
		}
	}
	return tot;
} 


vector<string> callParser()
{
	
  
     //taking input
   float time;
   int V,k;
   cin>>time;

   cin>>V;
   
   string vocabLetter;
   for(int i=0;i<V;i++)
   {
       cin>>vocabLetter;
       charIndex.insert(make_pair(vocabLetter[0],i));
   }
   charIndex.insert(make_pair('-',V));



   cin>>k;
   vector<string> input(k);
   for(int i=0;i<k;i++)
   {
       cin>>input[i];
   }


   cin>>CC;

   for(int i=0;i<V+1;i++)
   {
       for(int j=0;j<V+1;j++)
       {
           cin>>costArr[i][j];
       }
   }
   return input;
}

































