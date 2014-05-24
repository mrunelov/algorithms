
//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// geometry functions for working with lines, segments, points and polygons
//


#ifndef _GEOMETRY_KTH_
#define _GEOMETRY_KTH

#include "Point2.h"

#define INF 1000000
#define IN 1
#define ON 0
#define OUT -1
typedef int turn_t;
#define COUNTERCLOCKWISE -1
#define COLINEAR 0
#define CLOCKWISE 1
	
/*
 * Calculates the distance between a point and a segment
 */
template<typename T>
double point_segment_distance(point2<T> p, point2<T> a, point2<T> b)
{
    if (a == b)
        return point_distance(p,a);
    
    double segment_size = point_distance(a,b);
    double u = ((p.x - a.x)*(b.x-a.x) + (p.y-a.y)*(b.y-a.y))/(segment_size*segment_size);
    
    double x = a.x + u*(b.x-a.x);
    double y = a.y + u*(b.y-a.y);
    point2<T> projection(x,y);
    double line_projection_dist = point_distance(p, projection);
    
    if (point_distance(projection,a) + point_distance(projection,b) - point_distance(a,b) > 1e-8) // projection not on segment
    { 
        line_projection_dist = 1e9;
    }
    
    double endpoint1_dist = point_distance(p, a);
    double endpoint2_dist = point_distance(p, b);
    
    double result = min({line_projection_dist,endpoint1_dist, endpoint2_dist});
    return result;
}

/*
 * KATTIS: https://kth.kattis.scrool.se/problems/segmentdistance
 * 
 * Calculates the distance between two line segments
 */
template<typename T>
double segment_distance(point2<T> p1, point2<T> p2, point2<T> p3, point2<T> p4)
{
    // If the segments do not intersect, the distance is the shortest distance
    // between any two endpoints from different segments
    if (intersect(make_pair(p1,p2),make_pair(p3,p4)).empty()) 
    {
        double ans = point_segment_distance(p1, p3, p4);
        ans = min(ans, point_segment_distance(p2, p3, p4));
        ans = min(ans, point_segment_distance(p3, p1, p2));
        return min(ans, point_segment_distance(p4, p1, p2));
    }
    return 0.0;
}


/*
 * Checks the orientation of the three points p, q and r
 *
 * @return:
 *    -1: the orientation is counterclockwise
 *    0: the points are colinear
 *    1: the orientation is clockwise
 */
template<typename T>
int orientation(const point2<T>& p, const point2<T>& q, const point2<T>& r)
{
    int orientation = (int)((q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y));
    if (orientation == 0) return COLINEAR;
    return (orientation > 0) ? CLOCKWISE : COUNTERCLOCKWISE; // clockwise or counterclockwise
}
    
/*
 * iff p,q,r are colinear:
 * Checks whether p lies on the segment qr
 */
template<typename T>
bool onSegment(point2<T> p, point2<T> q, point2<T> r) 
{
    if (p.x <= max(q.x,r.x) && p.x >= min(q.x,r.x) && p.y <= max(q.y,r.y) && p.y >= min(q.y,r.y))
    {
        return true;
    }
    return false;
}

/*
 * KATTIS: https://kth.kattis.com/problems/segmentintersection
 *
 * Finds the intersection of two line segments
 *
 * Sources:
 * http://stackoverflow.com/a/1968345/645270
 * http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/ 
 *
 * @return:
 *     if the line segments do not intersect, an empty vector
 *     if they intersect in a point, a vector containing the point
 *     if they overlap, a vector containing the start and endpoints of the overlap
 */
template<typename T>
vector<point2<T>> intersect(pair<point2<T>, point2<T>> line1, pair<point2<T>, point2<T>> line2)
{
    vector<point2<T>> ans;
    point2<T> a = line1.first, b = line1.second, c = line2.first, d = line2.second;

    if (orientation(a,b,c) == 0 && orientation(a,b,d) == 0 && orientation(c,d,a) == 0 && orientation(c,d,b) == 0) { // all points colinear
        // order the points
        point2<T> min_line1 = min(a,b);
        point2<T> max_line1 = max(a,b);
        point2<T> min_line2 = min(c,d);
        point2<T> max_line2 = max(c,d);

        if (min_line1 < min_line2) 
        {
            if (max_line1 < min_line2) // disjoint
                return ans;
        }
        else if (min_line2 < min_line1)
        {
            if (max_line2 < min_line1) // disjoint
                return ans;
        }

        point2<T> overlap_start = max(min_line1,min_line2);
        point2<T> overlap_end = min(max_line1,max_line2);
        if (overlap_start == overlap_end) // overlap is one point
        { 
            ans.push_back(overlap_start);
        }
        else 
        {
            ans.push_back(overlap_start);
            ans.push_back(overlap_end);
        }
        return ans;

    }

    double x1 = (b.x - a.x), y1 = (b.y - a.y), x2 = (d.x - c.x), y2 = (d.y - c.y);
    double u_1 = (-y1*(a.x-c.x) + x1*(a.y-c.y))/(-x2*y1 + x1*y2);
    double u_2 = (x2*(a.y - c.y) - y2*(a.x-c.x))/(-x2*y1 + x1*y2);

    if (u_1 >= 0 && u_1 <= 1 && u_2 >= 0 && u_2 <= 1) // collision
    {
        double x = a.x + u_2*x1;
        double y = a.y + u_2*y1;
        ans.emplace_back(x,y);  
    }

    return ans;
}


/*
 * KATTIS: https://kth.kattis.com/problems/polygonarea
 *
 * Calculates the area of a polygon
 * 
 * @param points: the coordinates of vertices of a polygon
 * @return: If the points are in clockwise order, 
 *    it returns the area of the polygon, otherwise it returns (-area)
 */
template<typename T>
double polygon_area(vector< point2<T> > points) 
{
    double area = 0;
    int j = points.size() - 1; // index of last point
    rep(i, 0, points.size())
    {
        area += (points[j].x + points[i].x)*(points[j].y - points[i].y);
        j = i; // j points to previous point
    }
    return area*0.5;
}

/* 
 * KATTIS: https://kth.kattis.com/problems/pointinpolygon
 *
 * Checks if a point is inside, on our outside a polygon
 * 
 * @return:
 *    -1 if the point is outside the polygon
 *     0 if the point is on the edge of the polygon
 *     1 if the point is inside the polygon
 */
template<typename T>
int inside_poly(point2<T> p, vector<point2<T>> poly) 
{
    int intersections = 0;
    point2<T> inf_endpoint(INF, p.y);
    vector< point2<T> > intersection;
    
    int j = poly.size()-1;
    urep(i, 0, poly.size())
    {
        if (i != 0)
            j = i-1;

        if (p == poly[i] || p == poly[j])
            return ON;

        if (orientation(p,poly[i],poly[j]) == COLINEAR)
        {
            if (onSegment(p,poly[i],poly[j]))
                return ON;
        }
        intersection = intersect(make_pair(p, inf_endpoint), make_pair(poly[i],poly[j]));
        if (intersection.empty()) 
            continue;

        if (intersection.size() == 1)
        {

            if (poly[i] == intersection[0])
            {
                if (poly[j].y <= p.y)
                    continue;
            }

            if (poly[j] == intersection[0])
            {
                if (poly[i].y <= p.y)
                    continue;
            }                
            ++intersections;
        }
    }

    return intersections%2 == 0 ? OUT : IN;
}


/*
 * KATTIS: https://kth.kattis.com/problems/closestpair1
 * 
 * Finds the two closest points in an array of points
 *
 * @return: The index of the two closest points in the input array
 */
template<typename T>
pair<int,int> closestpair1(point2<T> points[], int N)
{
    typedef pair<int,point2<T> > p_i;
    vector<int> deltas = {0,0,-1,-1,1,1,0,-1,1,-1,-1,0,0,1,1,0,-1,1};
    // int lower_bound = -100000;
    int upper_bound = 100000;
    bool checked;
    int gridsize = ceil(sqrt(N)*0.5);
    double gridlength = upper_bound*2/(double)gridsize;
    vector< vector< vector<p_i> > > grid(gridsize, vector< vector< p_i > >(gridsize, vector<p_i>()));
    
    rep(i, 0, N)
    {
        int gridX = floor((points[i].x+upper_bound)/gridlength);
        int gridY = floor((points[i].y+upper_bound)/gridlength);
        grid[gridX][gridY].emplace_back(i,points[i]);
    }

    double closest_distance = 1e13;
    pair<int,int> closest_pair;
    unordered_map<int,bool> checked_all;

    rep(i,0,gridsize)
    {
        rep(j,0,gridsize) // loop over the grid
        {
            rep(k, 0, grid[i][j].size()) // loop over each point in each square
            {
                p_i p = grid[i][j][k];

                for (int m = 0; m < deltas.size(); m+=2)
                {
                    int gridX = i + deltas[m];
                    int gridY = j + deltas[m+1];

                    if (gridX < gridsize && gridY < gridsize && gridX >= 0 && gridY >= 0)
                    {
                        // No need to check the neighbourhood of all squares
                        // OBS: Invalid optimization for e.g matches along a diagonal of squares
                        // OBS 2: checked_all will be set for this square
                        // One option: i%2 && j%2 (no overlap), and don't set checked_all
                        // if ((i + j)%2 && m > 0) // m > 0 is neighbourhood
                        //     break;

                        // Working version!
                        if (i%2 == 0 && j%2 && m > 0)
                        {
                            checked = false;
                            break;
                        }


                        if (checked_all[gridX*gridsize+gridY])
                            continue;

                        vector<p_i> square = grid[gridX][gridY];
                        rep(n,0,square.size()) // loop over all points in square
                        {
                            p_i p2 = square[n];

                            // if (checked_all[p2.first]) // already checked. maybe slower than not checking at all
                            //     break;

                            if (p.first == p2.first) // same point
                                continue;

                            double distance = square_point_distance(p.second,p2.second);

                            if (distance < closest_distance)
                            {
                                closest_distance = distance;
                                closest_pair = make_pair(p.first, p2.first);
                            }
                        }                    
                    }
                }
                checked = true;
            }
            if (checked)
                checked_all[i*gridsize+j] = true;
        }
    }

    return closest_pair;
}


template<typename T>
int number_of_colinear_bruteforce(vector<point2<T>>& P)
{
	int N = P.size();
	if (N == 1) return 1;

	int maxcolinear = 2;
	rep(i, 0, N)
	{
		rep(j, i+1, N)
		{
			int count = 2;
			rep(k, 0, N)
			{
				if (k == i || k == j) continue;

				point2<T> p = P[i], q = P[j], r = P[k];

				if (orientation(p, q, r) == COLINEAR)
					count++;
			}

			maxcolinear = max(maxcolinear, count);
		}
	}

	return maxcolinear;
}


template<typename T>
int number_of_colinear(vector<point2<T>>& P)
{
	typedef pair<point2<T>, double> apoint;
	int N = P.size();
	if (N == 1) return 1;
	int maxcolinear = 2;

	//choose p = P[ip] as pivot, sort by angles
	rep(ip, 0, N)
	{
		point2<T> p = P[ip];
		vector<apoint> points;
		rep(i, 0, N)
		{
			if (i != ip)
			{
				points.emplace_back(P[i], p.angle(P[i]));
			}
		}

		sort(points.begin(), points.end(), [](const apoint& a, const apoint& b)->bool
		{
			return a.second < b.second;
		});

		//max number of adjecent points with same angle
		int curr = 2;
		rep(i, 1, N - 1)
		{

			if (points[i].second == points[i - 1].second)
			{
				curr++;
				maxcolinear = max(maxcolinear, curr);
			}
			else
			{
				curr = 2;
			}
		}
	}

	return maxcolinear;
}


template<typename T>
void compute_convex_hull(point2<T> P[], vector<point2<T>>& hull, int N)
{
	if (N == 1)
	{
		hull.push_back(P[0]);
		return;
	}

	if (N == 2)
	{
		if (P[0] == P[1])
		{
			hull.push_back(P[0]);
			return;
		}

		hull.push_back(P[0]);
		hull.push_back(P[1]);
		return;
	}

	//find lowest point
	point2<T> start(0, (numeric_limits<T>::max)());
	vector<point2<T>> points;
	rep(i, 0, N)
	{
		points.push_back(P[i]);
		if ((P[i]).y < start.y)
		{
			start = P[i];
			continue;
		}
		if ((P[i]).y == start.y)
		{
			if ((P[i]).x < start.x)
			{
				start = P[i];
				continue;
			}
		}
	}

	sort(points.begin(), points.end(), [&](const point2<T>& a, const point2<T>& b)->bool
	{
		if (start.angle(a) == start.angle(b))
		{
			return point_distance(start, a) < point_distance(start, b);
		}
		return start.angle(a) < start.angle(b);
	});

	auto top2 = [](stack<point2<T>>& S)->point2<T> 
	{
		point2<T> first = S.top(); S.pop();
		point2<T> second = S.top(); S.push(first);
		return second;
	};

	// loop through each three-adjacent points
	stack<point2<T>> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);

	rep(i, 3, N)
	{
		while (orientation(top2(S), S.top(), points[i]) != COUNTERCLOCKWISE)
		{
			if (!S.empty())
			{
				S.pop();
			}
		}

		S.push(points[i]);
	}
	
	//stack, S, holds the hull
	while (!S.empty())
	{
		hull.push_back(S.top());
		S.pop();
	}
}

#endif