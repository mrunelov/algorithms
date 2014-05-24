//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#include "UnionFind.h"
#include "common.h"

//
// public methods
//

UnionFind::UnionFind(int n)
: N(n + 1), parent(new int[n + 1]), height(new int[n + 1])
{
	rep(i, 0, n + 1)
	{
		parent[i] = i;
		height[i] = 0;
	}
}

void UnionFind::Union(int p, int q)
{
	int A = Find(p);
	int B = Find(q);
	if (A == B) return; //already in same set

	if (height[A] < height[B])
		parent[A] = B;
	else if (height[A] > height[B])
		parent[B] = A;
	else
	{
		parent[B] = A;
		height[B]++;
	}
}

bool UnionFind::InSame(int p, int q)
{
	int id_p = Find(p);
	int id_q = Find(q);

	return id_p == id_q;
}


//
// private methods
//

int UnionFind::Find(int p)
{
	if (parent[p] == p)
		return p;

	int res = Find(parent[p]); //TODO: path compression
	parent[p] = res;
	return res;

}

UnionFind::~UnionFind()
{
	delete[] parent;
	delete[] height;
}
