#include "EulerianPath.h"

stack<int> pathStack;

pair<int,int> set_dummy(graph& G)
{
    int start = -1;
    int end = -1;
    node curr;
    for (int n = 0; n < G.V.size(); ++n) {
        curr = G.V[n];
        if (curr.inDeg == curr.outDeg) {
            continue;
        }
        if (curr.inDeg == (curr.outDeg - 1) && start == -1) start = n;
        else if (curr.inDeg == (curr.outDeg + 1) && end == -1) end = n;
        else return make_pair(-1,-1);
    }
    if (start == -1 && end == -1)
        return make_pair(0,-1);
    else {
        G.addEdge(end,start); // dummy edge to create tour
        // cout << "Adding dummy " << end << "," << start << endl;
    }
    if (start != -1 && end == -1) return make_pair(-1,-1);
    if (end != -1 && start == -1) return make_pair(-1,-1);
    return make_pair(start,end);
}

vector<int> eulerian_path(graph& G)
{
    bool hasDummy = false;
    pair<int,int> dummy = set_dummy(G);
    if (dummy.first == -1)
        return vector<int>();
    if (dummy.second != -1)
        hasDummy = true;
    eulerian_path(G,dummy.first);
    vector<int> path;
    vector<int> otherpath;
    bool partTwo = false;
    while(!pathStack.empty()) 
    {
        if (!path.empty() && !partTwo && hasDummy && pathStack.top() == dummy.first && path.back() == dummy.second) {
            partTwo = true;
        }
        else if (partTwo) {
            otherpath.push_back(pathStack.top());
        }
        else
            path.push_back(pathStack.top());
        pathStack.pop();
    }
    for (int i = 0; i < path.size(); ++i) {
        otherpath.push_back(path[i]);
    }

    // wrong path size for disconnected components?
    if (hasDummy && otherpath.size() != G.E.size())
        return vector<int>();
    if (!hasDummy && otherpath.size() != G.E.size()+1)
        return vector<int>();
    return otherpath;  
}

void eulerian_path(graph& G, int u)
{
    trav(e, G.getAdj(u))
    {
        if (G.E[(*e).idx].visited)
            continue;
        G.E[(*e).idx].visited = true;
        eulerian_path(G, (*e).to);
    }
    pathStack.push(u);
}
