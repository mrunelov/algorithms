//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#ifndef COMMON_H
#define COMMON_H

//
// Includes
//

#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <climits>
#include <functional>

//
// Windows macros
//

#ifdef WINDOWS
#define typeof decltype
#define isnan(x) (_isnan(x))
#define __builtin_expect(exp, c) (exp)
#define round(x) floor((x) + 0.5)
#endif


//
// macros
//

#define rep(i, a, b) for (int i = (a); i < (b); ++i)                         // for loop
#define rrep(i, b, a) for (int i = (b-1); i >= a; --i)                       // reverse for loop
#define urep(i, a, b) for (size_t i = (a); i < (b); ++i)                     // unsigned for loop
#define trav(it, v) for (auto it = (v).begin(); it != (v).end(); ++it)       // foreach loop
#define sgn(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))							 // determine the sign of x
#define STATIC_ASSERT( x ) typedef char __STATIC_ASSERT__[( x )?1:-1]
#define endline "\n";

using namespace std;



#endif