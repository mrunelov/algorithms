//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "kthalgorithms.h"

/*
 * https://kth.kattis.scrool.se/problems/fenwick
 */

FenwickTree::FenwickTree(int N) : N(N+1), tree(N+1,0) {}
FenwickTree::FenwickTree(FenwickTree& other) : tree(other.tree), N(other.N) {}

long long FenwickTree::Query(int idx) {
    --idx; // queries do not include tree[idx] (exclusive)
    if (idx == -1) // special case for querying tree[0], which should always return 0
        return 0;
    long long sum = tree[0];
    while (idx > 0) {
        sum += tree[idx];
        idx -= idx&(-idx);
    }
    return sum;
}

void FenwickTree::Update(int idx, long long val) {
    if (idx == 0) {
        tree[0] += val;
    }
    else {
        while (idx <= N) {
            tree[idx] += val;
            idx += idx&-idx;
        }
    }
}

FenwickTree::~FenwickTree(){}

