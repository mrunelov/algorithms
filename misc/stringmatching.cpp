//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/*
 * KATTIS: https://kth.kattis.scrool.se/problems/stringmatching
 */

typedef long long ll;
const unsigned PRIME_BASE = 459089, PRIME_MOD = 3613609;
vector<int> rabinkarp(const string T, const string P)
{
    vector<int> occurences;
    int N = T.size();
    int m = P.size();

    ll patternHash = 0, windowHash = 0;


    // rolling hash: T[0]*base^(m) + T[1]*base^(m-1) + ... + T[m]*1
    ll power = 1;
    rep(i, 0, m) 
    {
        patternHash = (patternHash*PRIME_BASE + P[i]) % PRIME_MOD;
        power = (power * PRIME_BASE) % PRIME_MOD; // calculate power used for hashing
    }


    rep(i, 0, N) 
    {
        windowHash = windowHash*PRIME_BASE + T[i]; // add last char from hash
        windowHash %= PRIME_MOD;

        if (i >= m)
        {
            windowHash -= power * T[i - m] % PRIME_MOD; // remove first char from hash
            if (windowHash < 0)
                windowHash += PRIME_MOD;
        }

        if (i >= m - 1 && patternHash == windowHash) // match?
        {
            if (T.substr(i-m+1, m) == P) // check for collisions
                occurences.push_back(i-m+1);
        }
    }

    return occurences;
}

