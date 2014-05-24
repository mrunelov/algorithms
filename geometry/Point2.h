//
// @authors:
// Martin Runelöv
// Philip Sköld
//

#ifndef POINT2_H
#define POINT2_H

#define PI 3.1415926535897932384626433
#define d2r(x) ((x)*((PI)/(180.0)))


/* Class for points in 2D eucledian space

implements:
 - addition/subtraction
 - scalar multiplication/division
 - dot-product
 - cross-product
 - distance
 - angles

 */
template<typename T>
struct point2
{
public:

	T x, y;

	point2()
		: x(0), y(0)
	{}

	point2(T x, T y)
		: x(x), y(y)
	{}

	point2(const point2& other)
		: x(other.x), y(other.y)
	{}
	/*
	 * assignment, copy operators
	 */

	point2<T>& operator= (const point2<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

    /*
     * comparator operators
     */
	bool operator< (const point2<T>& other) const
	{
		if (x < other.x) 
		{
			return true;
		}
		if (x == other.x) 
		{
			return y < other.y ? true : false;
		}
		return false;
	}

	bool operator== (const point2<T>& other) const 
	{
		if (x == other.x && y == other.y) return true;
		return false;
	}

	bool operator!= (const point2<T>& other) const
	{
		return !(*this == other);
	}


	/*
	 *  other operators (+, -, *, /, dot, 
	 */

	inline point2<T> operator+(point2<T> other) const
	{
		return point2<T>(x + other.x, y + other.y);
	}

	inline point2<T> operator-(point2<T> other) const
	{
		return point2<T>(x - other.x, y - other.y);
	}

	inline point2<T> operator*(point2<T> other) const
	{
		return point2<T>(x*other.x, y*other.y);
	}

	inline point2<T> operator/(point2<T> other) const
	{
		assert(other.x != 0 && other.y != 0);
		return point2<T>(x / other.x, y / other.y);
	}

	double dot(point2<T> other) const
	{
		//a · b = ax × bx + ay × by
		return x*other.x + y*other.y;
	}

	T cross(point2<T> other) const
	{
		//u x v = det(uv) = 	= u_x*v_y - u_y*v_x,
		return x*other.y - y*other.x;
	}

	double angle(point2<T> other) const
	{
		return atan2(other.y - y, other.x - x) * 180 / PI;
	}

	double length() const
	{
		return std::sqrt(pow(x, 2) + pow(y, 2));
	}

};

template<typename T> inline ostream& operator<<(ostream& out, point2<T> val)
{
	out << "(" << val.x << "," << val.y << ")";
	return out;
}
template<typename T> inline ostream& operator<<(ostream& out, point2<T>* val)
{
	out << "(" << val->x << "," << val->y << ")";
	return out;
}

/*
struct close_t
{
	pair<int, int> points;
	double dist;

	close_t(pair<int, int> ptns, double d)
		:points(ptns), dist(d)
	{}

	close_t()
		:points(-1, -1), dist(0)
	{}
}; */

template<typename T>
double point_distance(point2<T> a, point2<T> b) 
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x*x + y*y);
}

template<typename T>
double square_point_distance(point2<T> a, point2<T> b) 
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	return x*x + y*y;
}

#endif /* end header guard */