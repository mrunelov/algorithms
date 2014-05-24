//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/*
* KATTIS: https://kth.kattis.scrool.se/problems/knapsack
*
*/

vector<int> knapsack(int capacity, vector<item> items) {
    vector<vector<bool>> keep(items.size()+1, vector<bool>(capacity+1));
    vector<vector<int>> memo(items.size()+1, vector<int>(capacity+1));
    rep(c, 0, capacity+1)
        memo[0][c] = 0;

    // DP the optimal solution for the first i items with capacity c <= C
    // The following recursion is used: 
    // memo[i][c] = max(memo[i-1][c], v_i + memo[i-1]][c-w_i])
    //                   ^don't pick item    ^pick item
    rep(i, 1, items.size()+1)
    {
        rep(c, 0, capacity+1)
        {
            item current = items[i-1];
            int oldvalue = memo[i-1][c];
            int resultingvalue = (current.value + memo[i-1][c - current.weight]);
            if (current.weight <= c && resultingvalue > oldvalue)
            {
                keep[i][c] = true;
                memo[i][c] = resultingvalue;
            }
            else
            {
                memo[i][c] = memo[i-1][c];
                keep[i][c] = false;
            }
        }
    }

    //backtrack to find the list of items used
    vector<int> result;
    int c = capacity;
    rrep(i, items.size()+1, 1) // highest to lowest item
    {
        if (keep[i][c])
        {
            result.push_back(i-1);
            c = c - items[i-1].weight;
        }
    }

    return result;
}