//
// @authors:
// Martin Runelöv
// Philip Sköld
//

//
// Lab 2
//

//
// Includes
//

#include "common.h"
#include "Point2.h"
#include "geometry.h"

#ifdef WINDOWS
#include <cstdlib>
#endif

// KATTIS input/output functions
void KATTIS_points();
void KATTIS_polygonarea();
void KATTIS_pointinpolygon();
void KATTIS_segmentintersection();
void KATTIS_line_segment_distance();
void KATTIS_closestpair1();
void KATTIS_maximumcolinearpoints();
void KATTIS_convexhull();

point2<double> points[100000];
point2<int> convex_hull_points[100000];

int main() 
{
	//KATTIS_points();
    //KATTIS_polygonarea();
    // KATTIS_pointinpolygon();
	// KATTIS_segmentintersection();
	// KATTIS_line_segment_distance();
	// KATTIS_closestpair1();
	KATTIS_maximumcolinearpoints();
	// KATTIS_convexhull();
    return 0;
}

void KATTIS_points()
{
	point2<float> p1(3, 4);
	point2<float> p2(3, 1);
	point2<float>* pp = &p1;

	//cout << pp << endline;
	cout << p1 << endline;
	cout << p2 << endline;

	cout << "+ " << p1 + p2 << endline;
	cout << "- " << p1 - p2 << endline;
	cout << "* " << p1 * p2 << endline;
	cout << "/ " << p1 / p2 << endline;
	cout << "dot " << p1.dot(p2) << endline;
	cout << "cross " << p1.cross(p2) << endline;
	cout << "length(p1) " << p1.length() << endline;

	int stop = 1;
}

void KATTIS_closestpair1()
{
	int N;
	while (true)
	{
		scanf("%d", &N);
		if (N == 0) break;
        for(int i = 0; i < N; ++i)
        {
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
		
		pair<int, int> closest = closestpair1(points, N);

		printf("%.2lf %.2lf %.2lf %.2lf\n", points[closest.first].x, points[closest.first].y, 
											points[closest.second].x, points[closest.second].y);

		int stop = 1;
	}
}

void KATTIS_line_segment_distance()
{
	int _t; cin >> _t;
	point2<double> a, b, c, d;
	while (_t--)
	{
		int x1, y1, x2, y2, x3, y3, x4, y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		a = point2<double>(x1, y1);
		b = point2<double>(x2, y2);
		c = point2<double>(x3, y3);
		d = point2<double>(x4, y4);
		
        double distance = segment_distance(a, b, c, d); 
        if (abs(distance) < 5e-3) { // -0.00 check. not actually needed here.
            printf("%.2lf\n", 0.00);
        }
        else 
		  printf("%.2lf\n", segment_distance(a, b, c, d));

		int stop = 1;
	}
}//*/

void KATTIS_segmentintersection()
{
	int _t;
	cin >> _t;

	while (_t--)
	{
		int x1, y1, x2, y2, x3, y3, x4, y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

		pair<point2<double>, point2<double>> line1 = { point2<double>(x1, y1), point2<double>(x2, y2) };
		pair<point2<double>, point2<double>> line2 = { point2<double>(x3, y3), point2<double>(x4, y4) };

		vector<point2<double>> ans = intersect(line1, line2);
        trav(it, ans) // fix -0.00 issue
        {
            if (abs(it->x) < 5e-3)
            {
                it->x = 0.0;
            }
            if (abs(it->y) < 5e-3)
            {
                it->y = 0.0;
            }
        }
		if (ans.size() == 0)
		{
			cout << "none" << endline;
		}
		else if (ans.size() == 1)
		{
            printf("%.2lf %.2lf\n", ans[0].x, ans[0].y);
		}
		else
		{
            if (ans[0] < ans[1]) 
            {
                printf("%.2lf %.2lf %.2lf %.2lf\n", ans[0].x, ans[0].y, ans[1].x, ans[1].y);
            }
            else 
            {
                printf("%.2lf %.2lf %.2lf %.2lf\n", ans[1].x, ans[1].y, ans[0].x, ans[0].y);
            }
		}


		int stop = 1;
	}
}


void KATTIS_polygonarea() 
{
    int n;
    while(scanf("%d", &n) == 1 && n != 0) 
    {
        vector<point2<int> > polygon;
        int x,y;
        while(n--) 
        {
            scanf("%d %d", &x, &y);
            polygon.emplace_back(x,y);
        }
        double area = polygon_area(polygon);
        if (area < 0) 
        {
            printf("CCW %.1lf\n", -area);
        }
        else 
        {
            printf("CW %.1lf\n", area);   
        }
    }
}


void KATTIS_pointinpolygon() 
{
    int n;
    while(scanf("%d", &n) == 1 && n != 0) 
    {
        vector< point2<int> > polygon;
        int x,y,m;
        while(n--) 
        {
            scanf("%d %d", &x, &y);
            polygon.emplace_back(x,y);
        }
        scanf("%d", &m);
        while(m--) 
        {
            scanf("%d %d", &x, &y);            
            point2<int> p(x,y);
            int res = inside_poly(p, polygon);
			if (res == 1) 
            {
                printf("in\n");
            }
            else if (res == 0)
            {
                printf("on\n");
            }
            else if (res == -1) 
            {
                printf("out\n");
            }
        }
    }
}


void KATTIS_maximumcolinearpoints()
{
	int N;
	while (scanf("%d", &N) == 1 && N != 0)
	{
		vector<point2<int>> points(N);
		rep(i, 0, N) scanf("%d%d", &points[i].x, &points[i].y);

		int ncolinear = number_of_colinear(points);
		cout << ncolinear << endline;
	}
}


void KATTIS_convexhull()
{
	int N;
	while (scanf("%d", &N) == 1 && N != 0)
	{
		rep(i, 0, N) scanf("%d%d", &convex_hull_points[i].x, &convex_hull_points[i].y);
		
		vector<point2<int>> convexhull;
		compute_convex_hull(convex_hull_points, convexhull, N);

		cout << convexhull.size() << endline;
		rrep(j, convexhull.size(), 0)
		{
			cout << (convexhull[j]).x << " " << (convexhull[j]).y << endline;
		}

		int stop = 1;
	}
}

