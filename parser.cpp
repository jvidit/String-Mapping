//#include <iostream>
//#include <vector>
//#include <map>
//
//using namespace std;
//
//
//int costArr[30][30];
//map<char, int> getIndex;
//
//const int max_n = 7;
//
//class StateDashMove
//{
//
//    vector<string> v;
//    int cost;
//    pair<int, int> next;
//    int difference;
//
//    int calculateCost(int stringIndex,int charIndex);
//    void generateNeighbours();
//    void pr(vector<string> v);
//
//
//public:
//
//    StateDashMove(vector<string> v,int cost);
//    void mutateState();
//    int getCost();
//};
//
//
//
//int insertDashes(vector<string>&v, int n)                            //function adds dashes to make the size of string n
//{
//    int k = v.size();
//    int totDashes=0;
//    for(int i = 0;i<k;i++)
//    {
//        int l = n - v[i].size();
//        totDashes+=l;
//        while(l--)
//            v[i]+="-";
//    }
//    return totDashes;
//}
//
//int initialCost(vector<string> v)
//{
//    int k = v.size(), n = v[0].size();
//    int ansCost = 0;
//
//    for(int charInd=0;charInd<n;charInd++)
//    {
//        for(int i=0;i<k;i++)
//        {
//            int c1 = getIndex.at(v[i][charInd]);
//            for(int j=i+1;j<k;j++)
//            {
//                int c2 = getIndex.at(v[j][charInd]);
//                ansCost+=costArr[c1][c2];
//            }
//        }
//    }
//    return ansCost;
//}
//
//
//int main()
//{
//
//
//    //taking input
//    float time;
//    int V,k,CC;
//    cin>>time;
//
//    cin>>V;
//    for(int i=0;i<V;i++)
//    {
//        char c;
//        cin>>c;
//        getIndex.insert(make_pair(c,i));
//    }
//    getIndex.insert(make_pair('-',V));
//
//
//    cin>>k;
//    vector<string> input(k);
//    for(int i=0;i<k;i++)
//        cin>>input[i];
//
//
//    cin>>CC;
//
//    for(int i=0;i<V+1;i++)
//    {
//        for(int j=0;j<V+1;j++)
//        {
//            cin>>costArr[i][j];
//        }
//    }
//
//    //complete dashes and find initial cost
//    int tempCost = CC*insertDashes(input,max_n);
//    tempCost+=initialCost(input);
//    // cout<<"tempCost "<<tempCost<<endl;
//    // return 0;
//
//
//    //make states
//    StateDashMove s = StateDashMove(input,tempCost);
//    s.mutateState();
//    cout<<s.getCost()<<endl;
//
//
//
//
//    return 0;
//
//}
//
//
//
//
//
//
//
//
//StateDashMove::StateDashMove(vector<string> v,int cost)
//{
//    this->v=v;
//    this->cost=cost;
//    this->next = make_pair(-1,-1);
//    this->difference = 0;
//}
//
//
//int StateDashMove::calculateCost(int stringIndex, int charIndex)
//{
//    int k = v.size();
//    int oldCost = 0, newCost = 0;
//
//    int c1 = getIndex.at(v[stringIndex][charIndex]);
//    int c2 = getIndex.at(v[stringIndex][charIndex-1]);
//    for(int i=0;i<k;i++)
//    {
//
//        if(i!=stringIndex)
//        {
//            int c3 = getIndex.at(v[i][charIndex]);
//            int c4 = getIndex.at(v[i][charIndex-1]);
//
//            oldCost+=costArr[c1][c3];
//            oldCost+=costArr[c2][c4];
//
//            newCost+=costArr[c1][c4];
//            newCost+=costArr[c2][c3];
//        }
//    }
//    return newCost-oldCost;
//}
//
//void StateDashMove::generateNeighbours()
//{
//    int k = v.size(),n = v[0].size();
//
//    for(int i=0;i<k;i++)
//    {
//        for(int j=1;j<n;j++)
//        {
//            if(v[i][j]=='-' && v[i][j-1]!='-')
//            {
//                int temp = calculateCost(i,j);
//                cout<<difference<<" "<<temp<<endl;
//                if(difference>=temp)
//                {
//                    difference = temp;
//                    next.first = i;
//                    next.second = j;
//                }
//            }
//        }
//    }
//    pr(v);
//}
//
//void StateDashMove::pr(vector<string> v)
//{
//    int k = v.size(),n = v[0].size();
//
//    for(int i=0;i<k;i++)
//        cout<<v[i]<<endl;
//}
//
//
//void StateDashMove::mutateState()
//{
//    generateNeighbours();
//
//    cost-=difference;
//
//    if(next.first==-1)
//        return;
//    char temp = v[next.first][next.second];
//    v[next.first][next.second]=v[next.first][next.second-1];
//    v[next.first][next.second-1]=temp;
//    next=make_pair(-1,-1);
//    difference=0;
//    mutateState();
//}
//
//
//int StateDashMove::getCost()
//{    return this->cost;    }
//
//


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


using namespace std;

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



int arr[1000][1000];
string s1,s2;


int main()
{
    string s;
    vector<string> v;
    for(int i=0;i<3;i++)
    {
        cin>>s;
        v.push_back(s);
    }
    Heuristic temp = Heuristic(v);
    cout<<temp.getHeuristic()<<endl;
    
    return 0;
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
            cout<<v[i]<<" "<<v[j]<<" "<<h<<endl;
        }
    }
    return h;
}
