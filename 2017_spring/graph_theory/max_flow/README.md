Network Flow by Ford-Fulkerson Algorithm
====

- Introduction
This is a document for introducing how did I build this program to find the maximum flow and minimum cuts in a directed graph network based on Ford-Fulkerson. This document also presents how does the input data structured and what does the output result look like.

- Development Environment
    - Programming language: C++
    - Compiler: g++ 6.2.1
    - OS: Fedora 25

- Program architecture
    - Functions:
        ```C++
        main() // takes input data, runs other functions
        Edge_flow() // add every node, its edge, and the flow into Graph.
        Max_flow() // find the maximum flow using Ford-Fulkerson method.
        Min_cut() // find the minimum cuts after found the maximum flow.
        ```
    - Data structures:
        ```C++
        struct vertex{} // stores every input node information
        ```
- Input data
The input data is made by referring the graph on the assignment material;
the first line of input is the number of vertices `n` in the graph;
the following `n-1` lines are the vertices flow;
these lines present the how do the vertices flow from vertex No.1 to vertex N. n-1 (since the vertex N is the sink node, there is no flow from sink);
in each of the flow lines,
the first element is the vertex number;
the second element is the number of edges which are flow *forward* to the next vertex;
the rest of elements are the pairs of the next vertex `a` and flow `b`.
The test input data is like follows:
```
10
1 3 2 12 4 10 6 15
2 3 3 8 9 2 4 3
5 2 9 7 8 2
3 3 10 12 8 4 9 7
4 1 5 4
7 2 5 5 10 7
8 2 7 3 10 13
9 1 8 5
6 2 5 6 7 10
```
- Output data
The output result is followed the requirement:
first line is the value maximum flow `n` and space separated with the number of minimum cuts `m`;
the following `m` lines are the edges of minimum cuts and each of them ordered as *from_vertex, to_vertex, and flow*.
The test output data is like follows:
```
22 4
2 3 8
5 8 2
7 10 7
9 8 5
```

- About the author
The autor of this document and program is Liu, Xiao who is a Master & Ph.D. combined course student at PL Lab.

autor email: liuxiao@pnu.edu
website: liuxiaoworld.github.io/blog

- License
This program is *NO License constrained*. You can use it as free as you want.
