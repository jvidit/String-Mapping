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

using namespace std;

int cost_bound=INT_MAX;
int CC;
map<char,int> char_index;
int costArr[30][30];   //

struct state
{
  vector<string> initial_s;
  vector<string> final_s;
  int hn;
  int cost;

  // state(int hn, int cost, vector<string> ini, vector<string> fin)
  //       : hn(hn), cost(cost), initial_s(ini), final_s(fin)
  //   {
  //   }
};
struct CompareHeuristic {
    bool operator()(state const& s1, state const& s2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return s1.hn > s2.hn;
    }
};

void printstate(state s);
vector<state> getNeighbor(state s, int dash_cost);
int return_extracost(vector<string> cur);


class Heuristic
{
    int arr[1000][1000];
    vector<string> v;
    int h;

    void ini(string s1,string s2);
    int makedp(int i,int j,string s1,string s2);

public:
    Heuristic(vector<string> a);
    int getHeuristic();

};

void dfsB_B(state cur)
{
  vector<state> neighbours=getNeighbor(cur,CC);
  if(neighbours.size()==0 && cur.cost<cost_bound)
  {
      printstate(cur);
      cost_bound=cur.cost;
      return;
  }
  priority_queue<state, vector<state>, CompareHeuristic> Q;
  for(int i=0;i<neighbours.size();i++)
  {
    Q.push(neighbours[i]);
  }
  while(!Q.empty())
  {
    state next_nbr = Q.top();
    Q.pop();
    if(cur.cost+next_nbr.hn<cost_bound) //expand into it
    {
      dfsB_B(next_nbr);
    }
  }
  return;
}


vector<string> callParser(string filename)
{
	
  
     //taking input
   float time;
   int V,k,CC;
   cin>>time;

   cin>>V;
   
   string vocabLetter;
   for(int i=0;i<V;i++)
   {
       cin>>vocabLetter;
       char_index.insert(make_pair(vocabLetter[0],i));
   }
   char_index.insert(make_pair('-',V));



   cin>>k;
   vector<string> input(k);
   for(int i=0;i<k;i++)
   {
       cin>>input[i];
       reverse(input[i].begin(),input[i].end());
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



int main(int argc, char*argv[])
{
  freopen (argv[1],"r",stdin);
  freopen (argv[2],"w",stdout);
  
  
  state initial_state;
  vector<string> ini=callParser("a");
  vector<string> fin(ini.size(),"");
  int cost=0;
  Heuristic temp=Heuristic(ini);
  int hn=temp.getHeuristic();
  initial_state.initial_s=ini;
  initial_state.final_s=fin;
  initial_state.cost=cost;
  initial_state.hn=hn;
  //cout<<"dddddddddddddddddddddddddddddddddddddddddd";
  dfsB_B(initial_state);
  return 0;
}



int return_extracost(vector<string> cur)
{
  int n=cur.size();
  int cost=0;
  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      int ind1 = char_index[cur[i][0]], ind2 = char_index[cur[j][0]];
      cost+=costArr[ind1][ind2];
    }
  }
  return cost;
}






void printstate(state s)
{
  vector<string> rem=s.initial_s;
  vector<string> cur=s.final_s;
  cout<<"STATE PRINTED STARTED: "<<endl;
  cout<<"initial_s: "<<endl;
  for(int i=0;i<rem.size();i++)
    cout<<rem[i]<<endl;
  cout<<"final_s: "<<endl;
  for(int i=0;i<cur.size();i++)
    cout<<cur[i]<<endl;
  cout<<"COst: "<<s.cost<<endl;
  cout<<"STATE PRINTED END: "<<endl;

}

void printInt_State(state s)
{
  cout<<"INT_STATE"<<endl;
  for(int i=0;i<s.initial_s.size();i++)
  {
    cout<<"INITIAL: "<<s.initial_s[i]<<"    "<<"FINAL: "<<s.final_s[i]<<endl;
  }
  cout<<"COST: "<<s.cost<<endl;
}

vector<state> getNeighbor(state s, int dash_cost)
{
  //return newS;
  vector<state> neighbours;
  int k=s.initial_s.size();
  //int min=INT_MAX;
  //cout<<pow(2,k)<<endl;
  int flag = 0;
  for(int i=0;i<k;i++)
  {
    if(s.initial_s[i].size()!=0)
    {
      flag=1;
      break;
    }
  }
  if(!flag)
    return neighbours;

  int limit=pow(2,k);
  for(int i=1;i<limit;i++)
  {
    state newS;
    vector<string> temp;
    int t=i;
    int flag_empty=0;
    for(int j=0;j<k;j++)
    {
      int rem=t%2;
      t/=2;
      if(rem==1)
      {
        if(s.initial_s[j].size()==0)
            flag_empty=1;
        else
            temp.push_back(s.initial_s[j][0]+s.final_s[j]);
      }
      else
        temp.push_back("-"+s.final_s[j]);
    }
    if(flag_empty==1)
      continue;
    else
    {
      int extra_cost=return_extracost(temp);
      t=i;
      int no_of_dashes=0;
      for(int j=0;j<k;j++)
      {
        if(t%2==0)
          no_of_dashes++;
        t/=2;
      }
      int min=s.cost+extra_cost+no_of_dashes*dash_cost;
      newS.final_s=temp;
      int t=i;
      for(int m=0;m<k;m++)
      {
        int rem=t%2;
        t/=2;
        if(rem==0)
        {
          if(newS.initial_s.size()==k)
            newS.initial_s[m]=s.initial_s[m];
          else
            newS.initial_s.push_back(s.initial_s[m]);
        }
        else
        {
          if(s.initial_s[m].size()!=0)
          {
            if(newS.initial_s.size()==k)
              newS.initial_s[m]=((s.initial_s[m]).substr(1));
            else
              newS.initial_s.push_back((s.initial_s[m]).substr(1));
          }
          else
          {
            if(newS.initial_s.size()==k)
                newS.initial_s[m]="";
            else
            newS.initial_s.push_back("");
          }
        }
        Heuristic getHue = Heuristic(newS.initial_s);
        newS.hn = getHue.getHeuristic();
        newS.cost=s.cost+extra_cost+no_of_dashes*dash_cost;

        //printInt_State(newS);

      }
    }
    neighbours.push_back(newS);
  }
  return neighbours;
}












































void Heuristic::ini(string s1,string s2)
{
    int n = max(s1.size(),s2.size());

    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
            arr[i][j]=-1;
    }
    arr[s1.size()][s2.size()]=0;
}

int Heuristic::makedp(int i,int j,string s1,string s2)
{
    if(arr[i][j]!=-1)
        return arr[i][j];

    if(i==s1.size())
    {
        arr[i][j]=makedp(i, j+1,s1,s2)+1;
        return arr[i][j];
    }

    if(j==s2.size())
    {
        arr[i][j]=makedp(i+1, j,s1,s2)+1;
        return arr[i][j];
    }

    if(s1[i]==s2[j])
    {
        arr[i][j]=makedp(i+1,j+1,s1,s2);
        return arr[i][j];
    }

    arr[i][j]=min(makedp(i+1, j,s1,s2),makedp(i, j+1,s1,s2))+1;
    return arr[i][j];
}


Heuristic::Heuristic(vector<string> a)
{
    v=a;
    h=0;
}


int Heuristic::getHeuristic()
{
    int k=v.size();
    for(int i=0;i<k;i++)
    {
        for(int j=i+1;j<k;j++)
        {
            ini(v[i],v[j]);
            h+=makedp(0, 0, v[i], v[j]);
            //cout<<v[i]<<" "<<v[j]<<" "<<h<<endl;
        }
    }
    return h;
}
