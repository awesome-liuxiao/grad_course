#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <cmath>
#include <stdio.h>
#define MAX 100
using namespace std;

class Graph
{
private:
struct vertex
{
	int num;                    //vertex number
	int flag;                  // +/- direction
	int ver;                  //来自哪条边 which edge
	int flow;                 //流量标记 flow value
	vector<int>f_edge;        //前向边 forward
	vector<int>u;            //前向边的流量 forward flow
	vector<int>b_edge;        //后向边 backword
	vector<int>x;           //后向边的流量 backword flow
	vertex(int num,int flag,int flow) : num(num),flag(flag),flow(flow){       //  u.push_back(0);	x.push_back(0);
	}
};
int N;                      // vertices
vector<vertex>v;

public:
Graph(int n) : N(n)
{
	for(int i=0; i<=n; i++) // initilize the vertices.
	{
		vertex tmp(i,0,0);
		v.push_back(tmp);
		for(int j=0; j<=n; j++)
		{
			v[i].u.push_back(0);
			v[i].x.push_back(0);
		}
	}
	v[1].flag=-1;           //源点标记为-1 mark the source vertex
	v[1].flow=MAX;
}

void Edge_flow(int i,int j,int flow) // add edge with from and to vertices and flow.
{
	v[i].f_edge.push_back(j);
	v[i].u[j]=flow;
	v[j].b_edge.push_back(i);
}

int Max_flow() // algorithm for finding the max flow based on Ford_Fulkerson method
{
	queue<int>Q;
	Q.push(1);
	int max_f=0;
	while(!Q.empty())
	{
		int i=Q.front(); Q.pop();
		int l=v[i].flow;
		for(unsigned int k=0; k<v[i].f_edge.size(); k++) // find augment path
		{
			int j=v[i].f_edge[k];
			if(v[j].flag==0)
			{
				int r=v[i].u[j]-v[i].x[j];
				if(r>0)
				{
					l=min(l,r);
					v[j].flag=1; v[j].ver=i; v[j].flow=l;
					Q.push(j);
				}
			}
		}
		for(unsigned int k=0; k<v[i].b_edge.size(); k++)
		{
			int j=v[i].b_edge[k];
			if(v[j].flag==0)
			{
				int r=v[j].x[i];
				if(r>0)
				{
					l=min(l,r);
					v[j].flag=-1; v[j].ver=i; v[j].flow=l;
					Q.push(j);
				}
			}
		}
		if(v[N].flag!=0)
		{
			int j=N;
			max_f+=l;
			while(j!=1)
			{
				int k=v[j].ver;
				if(v[j].flag==1)
					v[k].x[j]+=l;
				if(v[j].flag==-1)
					v[j].x[k]-=l;
				j=k;
			}
			while(!Q.empty())
				Q.pop();
			for(int i=2; i<=N; i++)
				v[i].flag=0;
			Q.push(1);
		}

	}
	return max_f;
}

void Min_cut() // find the min cuts
{
	int minCutNum = 0;
	stringstream ss;
	for(int i=1; i<N; i++)
	{
		if(v[i].flag!=0)
		{
			for(unsigned int k=0; k<v[i].f_edge.size(); k++)
			{
				int j=v[i].f_edge[k];
				if(v[j].flag==0&&v[i].flag!=0) {
					minCutNum++;
					ss << i << " " << j << " " << v[i].u[j] << '\n';
				}
			}
		}
	}
	std::cout << minCutNum <<'\n';
	std::cout << ss.str();
}

};

int main()
{
	int ver;
	while(cin>>ver) // get the vertices number
	{
		Graph G(ver); // graph instance
		int edge;
		int to,flow;
		int from, verNum;
		for(int i = 0; i < ver; i++)
		{ // get the from vertex, to vertex, and their flow
			cin >> from;
			cin >> verNum;
			edge += verNum;
			for (size_t j = 0; j < verNum; j++) {
				cin >> to >> flow;
				G.Edge_flow(from, to, flow);
			}
		}
		cout<<G.Max_flow() << " ";
		G.Min_cut();
		cout<<endl;
	}
	return 0;
}
