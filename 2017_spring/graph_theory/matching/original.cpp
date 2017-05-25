#include<stdio.h>  
#include<memory.h>  
  
#define MAX 202  
bool flag,visit[MAX];    //记录V2中的某个点是否被搜索过  
int match[MAX];   //记录与V2中的点匹配的点的编号  
int cow, stall;   //二分图中左边、右边集合中顶点的数目  
int head[MAX];  
  
struct edge  
{  
    int to,next;  
}e[3000];  
int index_i;  
  
void addedge(int u,int v)  
{   //向图中加边的算法，注意加上的是有向边  
    //u为v的后续节点既是v---->u  
    e[index_i].to=v;  
    e[index_i].next=head[u];  
    head[u]=index_i;  
    index_i++;  
}  
  
  
// 匈牙利（邻接表）算法  
bool dfs(int u)  
{  
    int i,v;  
    for(i = head[u]; i != 0; i = e[i].next)  
    {  
        v = e[i].to;  
        if(!visit[v])   //如果节点v与u相邻并且未被查找过  
        {  
            visit[v] = true;   //标记v为已查找过  
            if(match[v] == -1 || dfs(match[v]))   //如果i未在前一个匹配M中，或者i在匹配M中，但是从与i相邻的节点出发可以有增广路径  
            {  
                match[v] = u;  //记录查找成功记录，更新匹配M（即“取反”）  
                return true;   //返回查找成功  
            }  
        }  
    }  
    return false;  
}  
int MaxMatch()  
{  
    int i,sum=0;  
    memset(match,-1,sizeof(match));  
    for(i = 1 ; i <= cow ; ++i)  
    {  
        memset(visit,false,sizeof(visit));   //清空上次搜索时的标记  
        if( dfs(i) )    //从节点i尝试扩展  
        {  
            sum++;  
        }  
    }  
    return sum;  
}  
  
int main(void)  
{  
    int i,j,k,ans,m;  
    while (scanf("%d %d",&cow, &stall)!=EOF)  
    {  
        memset(head,0,sizeof(head));    //切记要初始化  
        index_i = 1;  
        for (i = 1; i <= cow; ++i)  
        {  
            scanf("%d",&k);  
            for (j = 0; j < k; ++j)  
            {  
                scanf("%d",&m);  
                addedge(i , m);  
            }  
        }  
  
        ans = MaxMatch();  
        printf("%d\n",ans);  
    }  
    return 0;  
}