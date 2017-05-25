#include <iostream>
#include <fstream>
#include<memory.h>

using namespace std;

#define MAX 202
bool flag,visit[MAX];    //records visited vertex
int match[MAX];   //records matched vertex
int ver_X, ver_Y;   //vertices in X side and Y side.
int head[MAX];

ifstream fin("matching.inp");
ofstream fout("matching.out");

struct edge
{
    int to,next;
}e[3000];
int index_i;

void addedge(int u,int v)  // u is x, v is y.
{   //add edge with given two vertices
    //v---->u sequence
    e[index_i].to=v;
   // cout << "------111-------\n";
    e[index_i].next=head[u];
    head[u]=index_i;
    index_i++;
   // cout << "-----222--------\n";
}


// depth-first search
bool dfs(int u)
{
    int i,v;
    for(i = head[u]; i != 0; i = e[i].next)
    {
        v = e[i].to;
        if(!visit[v])   //if not visited
        {
            visit[v] = true;   //marking as visited
            if(match[v] == -1 || dfs(match[v]))   //either unmatched or has augmenting path
            {
                match[v] = u;  //records successful searching.
                return true;
            }
        }
    }
    return false; // not found
}
int MaxMatch()
{
    int i,sum=0;
    memset(match,-1,sizeof(match));
    for(i = 1 ; i <= ver_X ; ++i)
    {
        memset(visit,false,sizeof(visit));   //initialize
        if( dfs(i) )    //find match
        {
            //cout << "--" << i << endl;
            sum++;
        }
    }
    return sum;
}

int main(void)
{
    int j,x_dgree,ans,y_conn;
    //cin >> ver_X >> ver_Y;
    fin >> ver_X >> ver_Y;
    //cout << ver_X << " "<< ver_Y<<endl;
    memset(head,0,sizeof(head));    //init head
    index_i = 1;
    int x_index;
    while (x_index != ver_X)
    {
        //cin >> x_index;
        fin >> x_index;
        //cout << x_index;
        //cin >> x_dgree;
        fin >> x_dgree;
        //cout << " "<<x_dgree;
        for (j = 0; j < x_dgree; ++j)
        {
            //cin >> y_conn;
            fin >> y_conn;
            //cout <<" "<< y_conn;
            addedge(x_index , y_conn);
        }
        //cout<<endl;
    }

    ans = MaxMatch();
    //cout << "max matching is " << ans <<endl;
    fout << ans;
    fin.close();
    fout.close();
    return 0;
}
