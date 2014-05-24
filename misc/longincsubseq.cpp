//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/*
* Help function for lis.
* Finds the smallest element indexed in L that is >= element indexed at i
* using a binary search.
* returns an index in 'objects' such that objects[S[best]] >= objects[i]
*/
int binsearch_lis(vector<int> &objects, vector<int> &S, int L, int i)
{
    int low = 0, mid = -1, high = L-1, best = -1;
    while (high >= low) 
    {
        mid = low + (high-low)/2;
        if (objects[S[mid]] == objects[i])
            return -1;
        
        if (objects[S[mid]] < objects[i]) 
        {
            low = mid + 1;
        }
        else 
        {
            best = mid;
            high = mid - 1;
        }
    }
    return best;
}

/*
* KATTIS: https://kth.kattis.com/problems/longincsubseq
*/
vector<int> lis(vector<int> objects)
{
    if (objects.empty())
        return vector<int>();

    vector<int> res;
    int N = objects.size();
    vector<int> S(N);       // S[j] = position j <= L of smallest object that a LIS of length j end on
    vector<int> prev(N);    // prev[k] index of successor to objects[k]
    int L = 1;              // longest LIS found so far
    S[0] = 0;
    prev[0] = -1;

    // iteratively build S and prev (in O(nlog(n)))
    rep(i, 1, N)
    {
        if (objects[i] > objects[S[L-1]]) 
        {
            S[L] = i;
            prev[i] = S[L-1];
            ++L;
        }
        else 
        {
            int j = binsearch_lis(objects, S, L, i); // objects[S[j]] >= objects[i]
            if (j != -1) 
            {
                prev[i] = S[j-1];
                S[j] = i;
            }
        }
    }

    // backtrack to find the LIS
    int current = S[L-1];
    res.resize(L);
    rrep(i, L, 0) 
    {
        res[i] = current; 
        current = prev[current];
    }
    return res;
}
