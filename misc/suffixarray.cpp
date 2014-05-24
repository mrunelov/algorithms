//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/*
* KATTIS: https://kth.kattis.scrool.se/statistics/problem?id=suffixsorting
*/

SuffixArray::SuffixArray(string s) : S(s)
{
    //initialization
    N = S.size();
    int tmp[MAXN]; // temp array for building sa
    rep(i, 0, N)
    {
        r_sa[i] = S[i];  // initial pos of the char at i
        sa[i] = i;      // assume order
        tmp[i] = 0;     // used to calculate r_sa[]
    }

    // compare function for two "gap"-grams. sorts by previous "gap"-grams.
    auto cmp = [&](int i, int j)->bool
    {
        if (r_sa[i] == r_sa[j])
        {
            i += gap;
            j += gap;
            if (i < N && j < N)
                return r_sa[i] < r_sa[j];
            else
                return i > j;
        }
        return r_sa[i] < r_sa[j];
    };

    /*
    * Step 1: Sorting by 2^i-grams, using the lexicographic names from the previous iteration to enable comparisons in 2 steps (i.e. O(1) time) each
    * Step 2: Creating new lexicographic names
    */
    gap = 1;
    while (true)
    {
        //use previous pos (pos of 2^(i-1)-grams, stored in pos) to sort 2^i-grams
        sort(begin(sa), begin(sa) + N, cmp);

        // lexicographic renaming => store the pos of each gram in the sorted "gap"-grams (sa)
        rep(i, 0, N - 1)
        {
            int higher = cmp(sa[i], sa[i + 1]);     //since sa is sorted, increment pairwise
            tmp[i + 1] = tmp[i] + (higher ? 1 : 0);
        }

        rep(i, 0, N)
        {
            r_sa[sa[i]] = tmp[i]; // store 'previous' pos for each sa[i]
        }


        if (tmp[N - 1] >= N - 1) // repeat until all 2i-grams are different
            break;

        gap = gap * 2; // next iteration we check 2^(i+1)-grams
    }
}

int SuffixArray::getSuffix(int i)
{
    return sa[i];
}

int SuffixArray::getLCP(int i)
{
    return lcp[i];
}

void SuffixArray::buildLCP() 
{
    rep(i, 0, N) r_lcp[sa[i]] = i;
    lcp[0] = 0;
    int h = 0;

    rep(i, 0, N)
    {
        if (r_lcp[i] == 0) {
            lcp[i] = 0;
            continue;
        }
        if (r_lcp[i] > 0) {
            int j = sa[r_lcp[i]-1];
            while (i+h < N && j+h < N && S[i+h] == S[j+h]) ++h;
            lcp[r_lcp[i]] = h;
            if (h > 0) {
                --h; // continue from last h next time
            }
        }
    }
}

SuffixArray::~SuffixArray()
{
}
