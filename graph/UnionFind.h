//
// @authors:
//  Martin Runelöv
//  Philip Sköld
//

#ifndef UNIONFIND_H
#define UNIONFIND_H

/*
 * A data structure that handles union-find operations for sets
 */
class UnionFind
{
	int N;
	int* parent;
	int* height;

public:
	/*
	* Constructor. The initial sets are {1}, {2},..., {N}.
	*/
	UnionFind(int N);
	/*
	* Union the sets that contain parameters p and q
	*/
	void Union(int p, int q);

	/*
	* Checks if p and q are in the same set
	*/
	bool InSame(int p, int q);

	~UnionFind();

	/*
	* returns the (representative of the) set that contains p
	*/
	int Find(int p);
};

#endif // header guard