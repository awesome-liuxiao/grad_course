#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <stdio.h>
#define MAX 999999
using namespace std;

class Graph
{
private:
struct vertex
{
	int num;                    //编号
	int flag;                  //正向或负向标记
	int ver;                  //来自哪条边
	int flow;                 //流量标记
	vector<int>f_edge;        //前向边
	vector<int>u;            //前向边的流量
	vector<int>b_edge;        //后向边
	vector<int>x;           //后向边的流量
	vertex(int num,int flag,int flow) : num(num),flag(flag),flow(flow){       //  u.push_back(0);	x.push_back(0);
	}
};
int N;                      //边数
vector<vertex>v;
public:
Graph(int n) : N(n)
{
	for(int i=0; i<=n; i++)
	{
		vertex tmp(i,0,0);
		v.push_back(tmp);
		for(int j=0; j<=n; j++)
		{
			v[i].u.push_back(0);
			v[i].x.push_back(0);
		}
	}

	v[1].flag=-1;           //源点标记为-1
	v[1].flow=MAX;

}
void Edge_flow(int i,int j,int flow)
{
	v[i].f_edge.push_back(j);
	v[i].u[j]=flow;
	v[j].b_edge.push_back(i);
}
int Max_flow()
{

	queue<int>Q;
	Q.push(1);
	int max_f=0;
	while(!Q.empty())
	{
		int i=Q.front(); Q.pop();
		int l=v[i].flow;
		for(unsigned int k=0; k<v[i].f_edge.size(); k++)
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
			cout<<"One of the path is :";
			while(j!=1)
			{
				cout<<j<<" from ";
				int k=v[j].ver;
				if(v[j].flag==1)
					v[k].x[j]+=l;
				if(v[j].flag==-1)
					v[j].x[k]-=l;
				j=k;
			}
			cout<<1<<" and the flow is "<<l<<endl;
			while(!Q.empty())
				Q.pop();
			for(int i=2; i<=N; i++)
				v[i].flag=0;
			Q.push(1);
		}

	}
	return max_f;
}
void Min_cut()
{
	for(int i=1; i<N; i++)
	{
		if(v[i].flag!=0)
		{
			for(unsigned int k=0; k<v[i].f_edge.size(); k++)
			{
				int j=v[i].f_edge[k];
				if(v[j].flag==0&&v[i].flag!=0)
					cout<<"("<<i<<","<<j<<")"<<";  ";
			}
		}
	}
}

};
int main()
{
	// freopen("in.txt","r",stdin);
	// freopen("out.txt","w",stdout);
	int ver;

	while(cin>>ver)
	{
		Graph G(ver);
		int edge;
		cin>>edge;
		int i,j,flow;
		while(edge--)
		{
			cin>>i>>j>>flow; javascript:;
			G.Edge_flow(i,j,flow);
		}
		cout<<"The max_flow is :"<<G.Max_flow()<<endl;
		cout<<"One of the min_cut is :";
		G.Min_cut();
		cout<<endl;
	}
	// fclose(stdin);
	// fclose(stdout);
	return 0;
}
