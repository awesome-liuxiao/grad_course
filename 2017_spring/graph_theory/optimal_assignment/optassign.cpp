#include <cstdio>
#include <memory.h>
#include <algorithm>
using namespace std;

const int MAX = 1024;

int n;
int weight [MAX] [MAX];
int lx [MAX], ly [MAX];
bool sx [MAX], sy [MAX];
int match [MAX];


void init (int size);
bool path (int u);
int bestmatch (bool maxsum = true);

void init (int size)
{
    n = size;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf ("%d", &weight [i] [j]);
}


bool path (int u)
{
    sx [u] = true;
    for (int v = 0; v < n; v++)
        if (!sy [v] && lx[u] + ly [v] == weight [u] [v])
        {
            sy [v] = true;
            if (match [v] == -1 || path (match [v]))
            {
                match [v] = u;
                return true;
            }
        }
    return false;
}

int bestmatch (bool maxsum)
{
    int i, j;
    if (!maxsum)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                weight [i] [j] = -weight [i] [j];
    }

    for (i = 0; i < n; i++)
    {
        lx [i] = -0x1FFFFFFF;
        ly [i] = 0;
        for (j = 0; j < n; j++)
            if (lx [i] < weight [i] [j])
                lx [i] = weight [i] [j];
    }

    memset (match, -1, sizeof (match));
    for (int u = 0; u < n; u++)
        while (1)
        {
            memset (sx, 0, sizeof (sx));
            memset (sy, 0, sizeof (sy));
            if (path (u))
                break;

            int dx = 0x7FFFFFFF;
            for (i = 0; i < n; i++)
                if (sx [i])
                    for (j = 0; j < n; j++)
                        if(!sy [j])
                            dx = min (lx[i] + ly [j] - weight [i] [j], dx);
            for (i = 0; i < n; i++)
            {
                if (sx [i])
                    lx [i] -= dx;
                if (sy [i])
                    ly [i] += dx;
            }
        }

    int sum = 0;
    for (i = 0; i < n; i++)
        sum += weight [match [i]] [i];

    if (!maxsum)
    {
        sum = -sum;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                weight [i] [j] = -weight [i] [j];
    }
    return sum;
}


int main()
{
    int n;
    scanf ("%d", &n);
    init (n);
    int cost = bestmatch (true);

    for (int i = 0; i < n; i++)
    {
        printf ("%d -> %d\n", i+1, match [i]+1);
    }
    printf ("%d\n", cost);

    return 0;
}
