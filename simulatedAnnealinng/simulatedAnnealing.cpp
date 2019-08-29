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
#include <ctime>
//#include <bits/stdc++.h>

using namespace std;

int cost_bound=INT_MAX;
int CC;
map<char,int> charIndex;
int costArr[30][30];
double timeLimit;
double beginTime;
double timeThreshold=pow(10,6);


int bestMargin = 1;
int bestPercentage = 10;


float T0 = 100;
float alpha=1;
float T_thresh=24;
int hops;

//returns false if time is about to end
bool remTime();

void setT(int, int);
//takes input
vector<string> callParser();




//pre-processing, returns number of dashses inserted
int completeDashes(vector<string>&,int);
pair<int,vector<string> > completeDashesRandomized(vector<string>, int);



//cost calculation for a neighbour
int getDifference(vector<string>, int, int);
//turns input into its nearest neighbour, if possible. returns 1 or 0.
int minNeighbour(vector<string>&);

vector<string> annealing(vector<string>);



void pr(vector<string>);
int calcCost(vector<string>);			//gets cost of a state
int getMaxLength(vector<string>);
int getTotLength(vector<string>);
vector<int> getBestLengths(vector<int> v, int minLength);
float getSchedule(int);



int main(int argc, char*argv[])
{

	beginTime = clock();
	freopen (argv[1],"r",stdin);
    freopen (argv[2],"w",stdout);

    vector<string> dataset=callParser();

    int maxLength = getMaxLength(dataset);
    int totLength = getTotLength(dataset);

	vector<string> bestSet=dataset;
    int bestCost = -1;


    int restartsL1 = 50;




    vector<int> baseLengths;




    for(int i = maxLength;i<=totLength;i++)
    {

    	double bestLCost = -1,totLcost = 0;
    	for(int j = 0;j<restartsL1;j++)
    	{

    		pair<int,vector<string> > initialState = completeDashesRandomized(dataset,i);
    		//pr(initialState.second);

    		while(minNeighbour(initialState.second))
    			;


    		if(!remTime())
    			break;

    		int totCost = initialState.first*CC + calcCost(initialState.second);



    		if(bestCost==-1 || bestCost>totCost)
    		{
    			bestCost = totCost;
    			bestSet = initialState.second;
                cout<<bestCost<<endl;
                pr(bestSet);
                cout<<endl<<endl;
    		}		//
		// for(int i = 0;i<bestLengths.size();i++)
    // {
		//
    // 	double bestLCost = -1,totLcost = 0;
		// 	restarts=(int)(restarts*0.85);
    // 	for(int j = 0;j<restarts;j++)
    // 	{

    		if(bestLCost==-1 || bestLCost>totCost)
    			bestLCost=totCost;
    		//totLcost+=(double)totCost/restarts;
    	}

    	baseLengths.push_back(bestLCost);

    	if(!remTime())
    		break;
    	//cout<<i<<" "<<totLcost<<" "<<bestLCost<<endl<<endl;
    }


    vector<int> bestLengths = getBestLengths(baseLengths,maxLength);

		int restarts=50;

		

		while(remTime())
		{
		  for(int i = 0;i<bestLengths.size();i++)
		  {
		//
		// for(int i = 0;i<bestLengths.size();i++)
    // {
		//
    // 	double bestLCost = -1,totLcost = 0;
		// 	restarts=(int)(restarts*0.85);
    // 	for(int j = 0;j<restarts;j++)
    // 	{
				// cout<<"Restarts no."<<j<<endl;
    		pair<int,vector<string> > initialState = completeDashesRandomized(dataset,bestLengths[i]);
    		// pr(initialState.second);

				//annealing_start_time=clock();
				hops=0;
				initialState.second=annealing(initialState.second);
				// cout<<endl<<"hops: "<<hops<<" Temperature: "<<getSchedule(hops)<<" COST: "<<calcCost(initialState.second)<<endl;
				// pr(initialState.second);

    		if(!remTime())
    			break;

    		int totCost = initialState.first*CC + calcCost(initialState.second);



    		if(bestCost==-1 || bestCost>totCost)
    		{
    			bestCost = totCost;
    			bestSet = initialState.second;
                cout<<bestCost<<endl;
                pr(bestSet);
                cout<<endl<<endl;
    		}
    	}

    	if(!remTime())
    		break;
    	//cout<<i<<" "<<totLcost<<" "<<bestLCost<<endl<<endl;
    }



    //cout<<calcCost(dataset)+DashInsertionCost<<endl;
//    cout<<"Time taken "<<(clock()-beginTime)/pow(10,6)<<" secs\n";
//    cout<<bestCost<<endl;
    pr(bestSet);
    return 0;
}






















void pr(vector<string> v)
{
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<endl;
}




int minNeighbour(vector<string>& v)
{
	if(!remTime())
		return 0;

	int stringIndex=-1, switchIndex = -1, diff = 0,temp;
	for(int i=0;i<v.size();i++)
	{
		for(int j=0;j<v[0].size();j++)
		{
			if(v[i][j]=='-')
			{
				if(j<v[0].size()-1 && v[i][j+1]!='-')
				{
					temp = getDifference(v,i,j);
					if(temp<diff)
					{
						diff = temp;
						stringIndex=i;
						switchIndex=j;
					}
				}

				if(j>0 && v[i][j-1]!='-')
				{
					temp = getDifference(v,i,j-1);

					if(temp<diff)
					{
						diff = temp;
						stringIndex=i;
						switchIndex=j-1;
					}
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

	int diff = 0;


	int a1 = charIndex[v[stringIndex][switchIndex]], a2 = charIndex[v[stringIndex][switchIndex+1]];

	for(int i=0;i<v.size();i++)
	{
		int b1 = charIndex[v[i][switchIndex]];
		int b2 = charIndex[v[i][switchIndex+1]];

		int oldCost=costArr[a1][b1]+costArr[a2][b2];
		int newCost=costArr[a2][b1]+costArr[a1][b2];

		diff+=newCost-oldCost;
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
        sort(gen.begin(),gen.begin()+deficit+1);

        int ind1=0,ind2=0;
        string s="";
        while(ind1+ind2<length)
        {
            if(ind1+ind2==gen[ind2] && ind2<deficit)
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
   int V,k;
   cin>>timeLimit;
   timeLimit*=60*pow(10,6);

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
	 setT(k,V);
   return input;
}


int getMaxLength(vector<string> v)
{
	unsigned long ans = 0;
	for(int i=0;i<v.size();i++)
		ans=max(ans,v[i].size());
	return (int)ans;
}

int getTotLength(vector<string> v)
{
	unsigned long ans = 0;
	for(int i=0;i<v.size();i++)
		ans+=v[i].size();
	return (int)ans;
}


bool remTime()
{
	double currentTime = clock()-beginTime;
	if(timeLimit-currentTime<=timeThreshold)
		return false;
	return true;
}



vector<int> getBestLengths(vector<int> v, int minLength)
{
    vector<pair<int,int> > temp;
    for(int i=0;i<v.size();i++)
        temp.push_back(make_pair(v[i],i));
    sort(temp.begin(),temp.end());

    vector<int> ans;
    for(int i=0;i<=(bestPercentage*v.size())/100;i++)
    {
        for(int j=-bestMargin;j<=bestMargin;j++)
        {
            int toBePushed = max(min(temp[i].second + j,(int)v.size()),0);
            ans.push_back(toBePushed+minLength);
        }
    }

    sort(ans.begin(),ans.end());
    vector<int>::iterator ip;
    ip = unique(ans.begin(), ans.end());
    ans.resize(distance(ans.begin(), ip));
    return ans;
}


pair<int , int > getRandomNeighbor(vector<string> state)
{
	//if(!remTime())
	//	return 0;
	vector< pair<int,int> > result;
	int stringIndex=-1, switchIndex = -1, diff = 0,temp;
	int res_num=0;
	for(int i=0;i<state.size();i++)
	{
		for(int j=0;j<state[0].size();j++)
		{
			if(state[i][j]=='-')
			{
				if(j<state[0].size()-1 && state[i][j+1]!='-')
				{
					temp = getDifference(state,i,j);

					result.push_back(make_pair(i,j));
				}

				if(j>0 && state[i][j-1]!='-')
				{
					temp = getDifference(state,i,j-1);
					result.push_back(make_pair(i,j-1));
				}
			}
		}
	}
	int ran = (int)(result.size()*rand()/RAND_MAX);
	// stringIndex=result[ran].first;
	// switchIndex=result[ran].second;
	// swap(state[stringIndex][switchIndex],state[stringIndex][switchIndex+1]);
	return result[ran];
}


float getSchedule(int t)
{
	//return T0*exp(-alpha*t);
	return T0/(1+sqrt(1+t));
	// return T0/(1+log10(1+t));
}



vector<string> annealing(vector<string> current)
{
	int checker=0;
	float T = getSchedule(hops);
	// cout<<T<<endl;
	while(T>(T0/40) && remTime())
	{
		T = getSchedule(hops);
		// cout<<hops<<" "<<T<<endl;
		hops++;
		int cost_cur=calcCost(current);
		pair<int, int>  randomState = getRandomNeighbor(current);
		int cost_fin=cost_cur+getDifference(current , randomState.first, randomState.second);
		if(cost_cur>cost_fin)
		{
			 swap(current[randomState.first][randomState.second],current[randomState.first][randomState.second+1]);
		}
		else
		{
			float prob=exp((cost_cur-cost_fin)/T);
			float k = (float) rand()/RAND_MAX;
			//cout<<"probability= "<<prob<<" k= "<<k<<endl;
			// cout<<"T: "<<T<<" Cost dif"<<cost_cur-cost_fin<<" Prob: "<<prob<<" hop: "<<hops<<" random no.: "<<k<<endl;
			if(k<prob)
			{
			 	swap(current[randomState.first][randomState.second],current[randomState.first][randomState.second+1]);
				// cout<<"Checker: "<<checker<<endl;
				// cout<<"T: "<<T<<" Cost dif"<<cost_cur-cost_fin<<" Prob: "<<prob<<" hop: "<<hops<<" random no.: "<<k<<endl;
				checker=0;
		 	}
			checker++;
		}
	}
	return current;
}


void setT(int k,int v)
{
		int dashMax = 0,totMax=0;
		for(int i=0;i<=v;i++)
			dashMax = max(dashMax,costArr[v][i]);

		for(int i=0;i<v;i++)
		{
			for(int j=0;j<v;j++)
				totMax = max(totMax, costArr[i][j]);
		}

		T0 = (k-1)*(dashMax + totMax);


}
