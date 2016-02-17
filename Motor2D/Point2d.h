//=================================
// include guard
#ifndef __Point2d_H__
#define __Point2d_H__

template <class TYPE>
class Point2d {

public:

	TYPE x, y;

	Point2d()
	{ }

	Point2d(const Point2d &p)
	{
		x = p.x;
		y = p.y;
	}

	Point2d(const TYPE &px, const TYPE &py)
	{
		x = px;
		y = py;
	}

	Point2d &set(const TYPE &px, const TYPE &py)
	{
		x = px;
		y = py;
		return (*this);
	}

	Point2d operator+ (const Point2d &p) const
	{
		Point2d tmp;
		tmp.x = x + p.x;
		tmp.y = y + p.y;
		return tmp;
	}

	Point2d operator- (const Point2d &p) const
	{
		Point2d tmp;
		tmp.x = x - p.x;
		tmp.y = y - p.y;
		return tmp;
	}

	const Point2d& operator+= (const Point2d &p)
	{
		x += p.x;
		y += p.y;
		return (*this);
	}

	const Point2d& operator-= (const Point2d &p)
	{
		x -= p.x;
		y -= p.y;
		return (*this);
	}

	bool operator== (const Point2d &p) const
	{
		return (x == p.x && y == p.y);
	}

	bool operator!= (const Point2d &p) const
	{
		return (x != p.x || y != p.y);
	}

	bool isBothZero() const
	{
		return (x == 0.0f && y == 0.0f);
	}

	void setZero()
	{
		x = y = 0;
	}

	TYPE distanceTo(const Point2d &p) const
	{
		TYPE dx = x - p.x;
		TYPE dy = y - p.y;
		return sqrt(dx*dx + dy*dy);
	}

	bool isClosedTo(const Point2d &p, float delta) const
	{
		return (abs(p.x - x) <= delta && abs(p.y - y) <= delta);
	}

};

typedef Point2d<int> iPoint;

#endif // !__Point2d_H__
