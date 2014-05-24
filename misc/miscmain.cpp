//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// Includes
//

#include "common.h"
#include "kthalgorithms.h"
#include "graph.h"

#ifdef WINDOWS
#include <cstdlib>
#endif

//
// Lab 1
//


// KATTIS input/output functions
void intervalCover();
void fenwick();
void unionfind();
void knapsack();
void longincsubseq();
void stringmatching();
void suffixsorting();
void shortestPathNonNegative();

int main() {
    // OBS only one active at a time
	// intervalCover();
	// knapsack();
	// longincsubseq();
	// unionfind();
	// fenwick();
	// stringmatching();
	//suffixsorting();
	//shortestPathNonNegative();

    return 0;
}

void longincsubseq() {
    int N;
    vector<int> res;
    while(scanf("%d", &N) == 1) {
        vector<int> seq(N);
        for (int i = 0; i < N; ++i) scanf("%d", &seq[i]);
        res = lis(seq);
        cout << res.size() << "\n";
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        // if (!res.empty())
        cout << endl;
    }
}

void intervalCover() {
    int N;
    double start, end;
    vector<int> res;
    while(scanf("%lf%lf", &start, &end) == 2) {
        Interval interval(start,end);
        scanf("%d", &N);
        vector<Interval> intervals(N);
        for (int i = 0; i < N; ++i) {
            scanf("%lf%lf", &start, &end);
            intervals[i].start = start;
            intervals[i].end = end;
            intervals[i].index = i;
        }
        res = cover(interval, intervals);
		if (!res.empty()) {
            cout << res.size() << "\n";
			for (int i = 0; i < res.size(); ++i) cout << res[i] << " ";
        }
		else
			cout << "impossible";
        cout << endl;
    }
}

void knapsack() {
    float C;
    int N, value, weight;
    vector<int> res;
    while(scanf("%f%d", &C, &N)==2) {
        vector<item> items(N);
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &value, &weight);
            items[i].value = value;
            items[i].weight = weight;    
        }
         int capacity = floor(C); //sufficient for integer weights
         res = knapsack(capacity,items);
         cout << res.size() << "\n";
         for (int i = 0; i < res.size(); ++i) {
             cout << res[i] << " ";
         }
         if (!res.empty())
            cout << endl;
    }
    cout << flush;
}

void unionfind()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    UnionFind sets(N);
    rep(i, 0, Q)
    {
        string op;
        int a, b;
        cin >> op;
        if (op == "=") // union(a, b)
        {
            scanf("%d %d", &a, &b);
            sets.Union(a, b);
        }
        else if (op == "?") // a and b in same?
        {
            scanf("%d %d", &a, &b);
            string ans = sets.InSame(a, b) ? "yes" : "no";
            cout << ans << endline;
        }
    }
}


void fenwick()
{
	int N; // arraylength, 1 <= N <= 5 000 000
	int Q; // nOperations, 0 <= M <= 5 000 000
	scanf("%d %d", &N, &Q);
    // ios::sync_with_stdio(false);
    cin.tie(NULL);

	FenwickTree tree(N);
	rep(m, 0, Q)
	{
		int i;
        long long delta;
		string op;
		std::cin >> op;
		if (op == "+")  // idx, val   => a[i] is incremented by delta, |delta| <= 1 000 000 000.
		{
    		scanf("%d %lld", &i, &delta);
    		tree.Update(i, delta);
        }
		else if (op == "?") { // i => a[0] + a[1] + ... + a[i-1], i=0 is empty sum.
			scanf("%d", &i);
			long long ans = tree.Query(i);
			printf("%lld\n", ans);
		}
	}
    cout << flush;
}


void stringmatching()
{
	string text;
	string pattern;
	while (getline(cin, pattern) && getline(cin, text))
	{
		vector<int> answers = rabinkarp(text, pattern);

		//cout << "pattern: " << pattern << endl;
		//cout << " in: " << text << endl;

		//cout << endl;
		rep(i, 0, answers.size())
			cout << answers[i] << " ";

		//if (answers.size() == 0)
		//	cout << "-";

		cout << endl;

			
	}
	int stop = 0;
}


void suffixsorting()
{
	int n;
	string s;
	while (getline(cin, s))
	{
		SuffixArray sarr(s);
		cin >> n;
		rep(_i, 0, n)
		{
			int i;
			cin >> i;

			int ans = sarr.getSuffix(i);
			cout << ans << " ";
		}
		cout << endline;
		getline(cin, s); // eat "\n" before next test case
	}
}


//
// GRAPH WEEK
//

void shortestPathNonNegative()
{
	graph G(10);
	G.addEdge(0, 3, 5);
	G.addEdge(0, 5, 3);


	cout << G.getAdj(0)[0].to << "(" << G.getAdj(0)[0].w << ")" << endline;
	cout << G.getAdj(0)[1].to << endline;


	int stop = 0;
}

