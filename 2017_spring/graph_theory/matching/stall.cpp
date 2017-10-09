/*
ID: cmykrgb1
PROG: stall4
LANG: C++
*/
#include<memory.h>
#include <iostream>
#include <fstream>
#define MAX 402
#define PV 200
using namespace std;
ifstream fi("stall2.in");
ofstream fo("stall.out");
int N,M,mat;
int adjl[MAX][MAX];
int match[MAX];
bool onpath[MAX];

void init()
{
    int i,j,a,b;
    fi >> N >> M;
    for (i=1;i<=N;i++)
    {
        fi >> a;
        for (j=1;j<=a;j++)
        {
            fi >> b;
            adjl[i][ ++adjl[i][0] ]=b+PV;
            adjl[b+PV][ ++adjl[b+PV][0] ]=i;
        }
    }
}

bool cross(int i)
{
    int k,j;
    for (k=1;k<=adjl[i][0];k++)
    {
        j=adjl[i][k];
        if (!onpath[j])
        {
            onpath[j]=true;
            if (!match[j] || cross(match[j]))
            {
                match[j]=i;
                return true;
            }
        }
    }
    return false;
}

void hungary()
{
    int i;
    for (i=1;i<=N;i++)
    {
        if (cross(i))
            mat++;
        memset(onpath,0,sizeof(onpath));
    }
}

void print()
{
    fo << mat << endl;
    fi.close();
    fo.close();
}

int main()
{
    init();
    hungary();
    print();
    return 0;
}