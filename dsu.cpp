/*
Note for me:
1) DSU ignores extra edge of same component
2) DSU is connected graph with minimum edges ( for visualization )
3) Whenever a question is related to components think of DSU
*/

#include <bits/stdc++.h>
using namespace std;

// ! Don't use both DSU by rank and DSU by size (Use either of them)

// ? What is DSU?
//  Union(u,v) => EG:- Node 1 and Node 5 as single components -> Union(1,5) => Connects 1 and 5
//      1. Find ultimate parent of u and v (ulpu,ulpv)
//      2. Find rank of ulpu and ulpv  (By rank)
//      3. Connect smaller rank to larger rank always   (Larger one will have higher level (rank))
//          [If we connect larger to smaller the height of the tree increases]
class DisjointSet
{
    vector<int> rank, parent, size;

public:
    // Initial configuration constructor
    DisjointSet(int n)
    {
        // (n+1) works for both 0 and 1 based indexing
        // rank represents something like level (It increase upways and not downside)
        rank.resize(n + 1, 0);
        // Initially everyone is single component so size is 1
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }
    // Ultimate Parent => top most parent (Head)
    int findUltimateParent(int node)
    {
        // base case
        if (parent[node] == node)
            return node;
        // For long trees we take logN time to find ultimate parent
        // So, as we find ulti parent once for eg the leaf node, we update its parent to the ulti parent of that component

        // PATH COMPRESSION
        return parent[node] = findUltimateParent(parent[node]);
        // Now, it would take constant time to find ultimate parent
        // Basically, we are just attaching a node to its ultimate parent directly
    }
    // Attaching nodes by following the 3 steps written above
    void unionByRank(int u, int v)
    {
        // 1. Find ulti parent
        int ulpu = findUltimateParent(u);
        int ulpv = findUltimateParent(v);
        // If both equal means already connected
        if (ulpu == ulpv)
            return;
        // 2. Find rank of the ulti parent & 3. Attach smaller one to the larger one
        if (rank[ulpu] < rank[ulpv])
        {
            // Attaching smaller to larger one => level (rank) size won't be affected
            parent[ulpu] = ulpv;
        }
        else if (rank[ulpv] < rank[ulpu])
        {
            parent[ulpv] = ulpu;
        }
        else
        {
            // both rank equal => attach to anyone and increase it's rank (level) size
            parent[ulpv] = ulpu;
            rank[ulpu]++;
        }
    }
    // Attaching nodes by just replacing rank (level) to size in step 2.
    void unionBySize(int u, int v)
    {
        int ulpu = findUltimateParent(u);
        int ulpv = findUltimateParent(v);
        if (ulpu == ulpv)
            return;
        if (size[ulpu] < size[ulpv])
        {
            parent[ulpu] = ulpv;
            size[ulpv] += size[ulpu];
        }
        else
        {
            parent[ulpv] = ulpu;
            size[ulpu] += size[ulpv];
        }
    }
};