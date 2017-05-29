#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#define maxn 222
#define inf 0x3f3f3f3f
using namespace std;
struct edge {
	int to;
	int cap;
	int rev;
};
vector<edge>e[maxn];
int book[maxn];
int dfs(int cur,int end,int flow){
	if(cur == end)
		return flow;
	book[cur] = 1;
	for(int i = 0; i<e[cur].size(); i++) {
		edge &temp = e[cur][i];
		if(!book[temp.to] && temp.cap>0) {
			int d = dfs(temp.to,end,min(flow,temp.cap));
			if(d > 0) {
				temp.cap -= d;
				e[temp.to][temp.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF) {
		for(int i = 1; i<=n; i++)
			e[i].clear();
		int u,v,w;
		for(int i = 0; i<n; i++) {
			scanf("%d%d%d",&u,&v,&w);
			e[u].push_back((edge){v,w,e[v].size()});
			e[v].push_back((edge){u,0,e[u].size()-1});
		}
		int ans = 0;
		while(1) {
			memset(book,0,sizeof(book));
			int temp = dfs(1,m,inf);
			if(temp == 0)
				break;
			ans += temp;
		}
		printf("%d\n",ans);
	}
	return 0;
}
