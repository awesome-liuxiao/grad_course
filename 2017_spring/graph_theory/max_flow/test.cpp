#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

int N,M;  //边数，顶点数
const int maxN=201;
bool visited[maxN];
int pre[maxN];          //前驱节点
int c[maxN][maxN];
int ans;

void Ford_Fulkerson()
{
	while(1)
	{
		queue<int> q;
		memset(visited,0,sizeof(visited));
		memset(pre,-1,sizeof(pre));
		q.push(0);  //第一个定点入队
		visited[0]=1; //打上已经被访问的标记
		while(!q.empty())
		{
			int now=q.front();
			if(now==M-1) //注意：找到一条增广路径后就跳出循环
				break;
			q.pop();
			for(int i=0; i<M; i++)
			{
				if(c[now][i]&&!visited[i])
				{
					q.push(i);
					visited[i]=1;
					pre[i]=now;
				}
			}
		}
		if(!visited[M-1])
			break;
		int min=0x7fffffff;
		for(int i=M-1; i>0; i=pre[i]) //注意For循环的条件
		{
			if(c[pre[i]][i]<min)
				min=c[pre[i]][i];
		}

		for(int i=M-1; i>0; i=pre[i])
		{
			c[pre[i]][i]-=min; //前向弧增加min
			c[i][pre[i]]+=min; //后向弧减小min
		}
		ans+=min;
	}
}


int main()
{
	//ifstream cin;
	//cin.open("input.txt");
	while(cin>>N>>M)
	{
		int v,s,w;
		ans=0;
		memset(c,0,sizeof(c));
		for(int i=0; i<N; i++)
		{
			cin>>v>>s>>w;
			c[v-1][s-1]+=w;
		}

		//cin.close();

		Ford_Fulkerson();
		cout<<ans<<endl;
	}
	return 0;
}
