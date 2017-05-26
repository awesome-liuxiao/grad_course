#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;
int maper[205][205],pre[205];
int e_num,v_num;
queue<int>fp;
bool bfs(int src,int des)
{
	int index,i;
	memset(pre,-1,sizeof(pre));
	while(!fp.empty()) fp.pop();
	pre[src]=src;
	fp.push(src);
	while(!fp.empty())
	{
		index=fp.front();
		fp.pop();
		for(i=1; i<=v_num; i++)
		{
			if(pre[i]==-1&&maper[index][i]>0)
			{
				pre[i]=index;
				fp.push(i);
				if(i==des) return true;
			}
		}
	}                                               //寻找增广路径
	return false;
}
int maxflow(int src,int des)
{
	int i,jieguo=0,minflow;
	while(bfs(src,des))
	{
		minflow=INF;
		for(i=des; i!=src; i=pre[i])
			minflow=min(minflow,maper[pre[i]][i]);
		for(i=des; i!=src; i=pre[i])
		{
			maper[pre[i]][i]-=minflow;
			maper[i][pre[i]]+=minflow;
		}
		jieguo+=minflow;
	}
	return jieguo;
}
int main()
{
	//freopen("input","r",stdin);
	int i;
	int u,v,w;
	while(scanf("%d %d",&e_num,&v_num)!=EOF)
	{
		memset(maper,0,sizeof(maper));
		for(i=1; i<=e_num; i++)
		{
			cin >> u >> v >> w;
			maper[u][v]+=w;
		}
		int ans=maxflow(1,v_num);
		cout << ans << endl;
	}
	return 0;
}
