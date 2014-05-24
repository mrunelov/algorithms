//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "EdmondsKarp.h"


t_edgeset EdmondsKarp(FlowGraph& G)
{
    //answer containers
    vector<Edge> usedEdges;
    long long maxflow = 0;

    //initialize BFS_ID
    BFS_ID = 0;

    // each iteration consider flows at least CAPACITY_THRES.
    // Decrease this thres until all flows (>= 1) have been considered
    while (G.CAPACITY_THRES >= 1)
    {
        int residual;
        while ((residual = getResidual(G)) != -1)
        {
            //increase flow
            maxflow += residual;

            //Augument Flow along path
            int curr = G.T;
            while (curr != G.S)
            {
                Edge* uv = &G.E[G.V[curr].edgeIn];
                Edge* vu = &G.E[uv->reverse];
                uv->flow += residual;
                vu->flow -= residual;
                
                curr = uv->from;
            }
        }

        G.CAPACITY_THRES /= 2; //decrease threshold for next iteration
    }

    //get used edges
    trav(e, G.E)
        if ((*e).flow > 0 && !(*e).isReverse)
            usedEdges.push_back((*e));

    return make_pair(usedEdges, maxflow);
}

int getResidual(FlowGraph& G)
{
    Node* source = &G.V[G.S];
    Node* sink = &G.V[G.T];

    // BFS
    BFS_ID++;
    vector<int> vis(G.N, -1);
    queue<Node*> q;

    vis[G.S] = BFS_ID;
    G.SetFlow(G.S, INT_MAX);
    q.push(source);
    while (!q.empty())
    {
        Node node = *q.front();
        q.pop();

        if (node.idx == G.T)
            return G.GetSink().currentflow;

        rep(i, 0, node.adj.size())
        {
            Edge edge = G.E[node.adj[i]];
            int restCapacity = edge.capacity - edge.flow;
            if (restCapacity >= G.CAPACITY_THRES && vis[edge.to] != BFS_ID)
            {
                //update flow & proceed with BFS
                Node* next = &G.V[edge.to];

                next->currentflow = min(G.V[edge.from].currentflow, restCapacity);
                next->prev = edge.from;
                next->edgeIn = node.adj[i];
                
                vis[next->idx] = BFS_ID;
                q.push(next);
            }
        }
    }

    // no residual (path) found
    return -1;
}
