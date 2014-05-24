//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/* Labb 1 - Popup14
 * authors: Martin Runelöv, Philip Sköld
 *
 */

/*
 * https://kth.kattis.com/problems/intervalcover
 */
vector<int> cover(Interval interval, vector<Interval> intervals) 
{
    double start, end;
    vector<int> cover;
    bool zeroInterval = interval.start == interval.end;

    sort(intervals.begin(), intervals.end()); // sorted by end

    double covered = interval.start;
    while (covered < interval.end || zeroInterval) 
    {
        int foundIndex = -1;
        for (int i = intervals.size()-1; i >= 0; --i) 
        {
            if (intervals[i].start > covered)
                continue; 
            if (intervals[i].end < covered) // no intervals can cover
                return vector<int>();

            foundIndex = i;
            covered = intervals[i].end;
            break;
        }

        if (foundIndex != -1) 
        {
            cover.push_back(intervals[foundIndex].index);
            intervals.erase(intervals.begin()+foundIndex);
        }
        else
        {
            return vector<int>();
        }

        if (zeroInterval) // 0-intervals only need one pass
            break;
    }
    if (covered < interval.end) 
        return vector<int>();
    
    return cover;
}