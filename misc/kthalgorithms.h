//
// @authors:
// Martin Runelöv
// Philip Sköld
//


//
// Static Library Code:
//



//
// lab.h
//

#ifndef KTH_ALGORITHMS_H
#define KTH_ALGORITHMS_H



#include "common.h"

//*****************//
// Interval Cover
//*****************//

/* 
 * Interval struct used in interval covering
 * @index: The original index of the interval in the list of intervals to use
 */
struct Interval {
	int index;
    double start;
    double end;
    Interval() : index(-1), start(0), end(0) {};
    Interval(double start, double end) : start(start), end(end) {};
    Interval(const Interval& other) : index(other.index), start(other.start), end(other.end) {};
    bool operator < (const Interval& i) const { return (end < i.end); } // compare intervals by end
};

/* 
 * KATTIS: https://kth.kattis.scrool.se/problems/intervalcover
 * Finds the minimum number of intervals that can be used to cover an interval
 *
 * @param interval: the interval to cover
 * @param intervals: the intervals to cover with
 * @return: a vector containing the indices of the intervals used to cover the interval,
            or an empty vector if no covering is found
 */
vector<int> cover(Interval interval, vector<Interval> intervals);



//***********//
// Knapsack
//***********//

/*
 * item struct for the knapsack problem.
 */
struct item
{
    int value;
    int weight;
};

/*
 * KATTIS: https://kth.kattis.scrool.se/problems/knapsack 
 * Solves 0/1-Knapsack in which we have a (weight) capacity and want to choose
 * items of certain weight and value such that the total weights are not above 
 * the capacity and the total value is maximized. 
 * 0/1 means that we either pick or don't pick an item.
 *
 * @param capacity: the capacity of the knapsack
 * @param items: the items to fill the knapsack with
 * @return: the indicies of the items used to fill the knapsack with maximized value
 */
vector<int> knapsack(int capacity, vector<item> items);



//********************************//
// Longest Increasing subsequence
//********************************//

/*
 * KATTIS: https://kth.kattis.com/problems/longincsubseq
 * Finds the longest increasing subsequence in an array of integers 
 *
 * @param objects: a vector of integers
 * @return: the indices in the vector for one longest increasing subsequence
 */
vector<int> lis(vector<int> objects);


//***************************//
// Fenwick Tree (prefix sums)
//***************************//

/*
 * KATTIS: https://kth.kattis.scrool.se/problems/fenwick 
 * Data structure for calculating and updating prefix sums.
 * @Update: increments index idx by val, including related prefix sums
 * @Query: returns the prefix sum for indices 0 to idx-1. index 0 always returns 0.
 */
class FenwickTree
{
	std::vector<long long> tree;
	int N;

public:
	FenwickTree(int N);
	FenwickTree(FenwickTree& other);

    /*
     * Updates the prefix sums
     * @param idx: index to update from
     * @param val: value to increment by
     */
    void Update(int idx, long long val);
	void UpdateLower(int idx, long long val);

    /*
     * Query the tree for prefix sums (exclusive)
     *
     * @param idx: index from which to sum prefix sums (exclusive)
     * @return: tree[0] + tree[1] + ... + tree[idx-1]
     */
	long long Query(int idx);

	~FenwickTree();
};


//*****************//
// String Matching
//*****************//

/*
 * KATTIS: https://kth.kattis.scrool.se/problems/stringmatching
 * Given a text T and a string pattern, P, finds all the occurrences of P
 * in T as a list of indices.
 * 
 * The implementation uses the Rabin-Karp algorithm with a rolling hash function. 
 * 
 * @param T: the text to search 
 * @param P: the pattern to find
 */
vector<int> rabinkarp(string T, string P);




//********************************************//
// Suffix Array & Longest Common Prefix Array
//********************************************//

/*
 * KATTIS: https://kth.kattis.scrool.se/statistics/problem?id=suffixsorting
 * Data structure for suffix arrays and longest common prefix (LCP) arrays
 */

class SuffixArray
{
	const static int MAXN = 100001;
	string S;
	int N, gap;

	int sa[MAXN], lcp[MAXN];
	int r_sa[MAXN], r_lcp[MAXN];

public:
    /*
     * Constructor. Builds a suffix array.
     * 
     * @param s: The string to build a suffix array of
     */
	SuffixArray(string s);
	int getSuffix(int i);
    int getLCP(int i);
	~SuffixArray();

private:
    /*
     * Constructs a longest common prefix (LCP) array using the suffix array
     */
	void buildLCP();
};







#endif /* end header guard */