#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include "p2Defs.h"
#include "Point2d.h"
#include <math.h>
#include <cmath>

template<class TYPE>
class Vector2D
{
public:
	Point2d<TYPE> position;
	TYPE x, y;

	Vector2D()
	{}

	Vector2D(const Vector2D<TYPE>& v)
	{
		this->position.x = v.position.x;
		this->position.y = v.position.y;
		this->x = v.x;
		this->y = v.y;
	}

	Vector2D(const TYPE& distance_x, const TYPE& distance_y, const TYPE& x = 0, const TYPE& y = 0)
	{
		this->position.x = x;
		this->position.y = y;
		this->x = distance_x;
		this->y = distance_y;
	}

	Vector2D& create(const TYPE& distance_x, const TYPE& distance_y, const TYPE& x = 0, const TYPE& y = 0)
	{
		this->position.x = x;
		this->position.y = y;
		this->x = distance_x;
		this->y = distance_y

			return(*this);
	}

	Vector2D& create(const TYPE& _x, const TYPE& _y)
	{
		x = _x;
		y = _y;
	}

	// Math ------------------------------------------------
	Vector2D operator -(const Vector2D &v) const
	{
		Vector2D r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	Vector2D operator +(const Vector2D &v) const
	{
		Vector2D r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const Vector2D& operator -=(const Vector2D &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const Vector2D<TYPE>& operator +=(const Vector2D<TYPE> &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}
	const Vector2D<TYPE>& operator *=(const float mult)
	{
		x *= mult;
		y *= mult;
		return (*this);
	}

	Vector2D<TYPE> operator *(const float mult) const
	{
		Vector2D<TYPE> newVec;
		newVec.x = x * mult;
		newVec.y = y * mult;
		return newVec;
	}

	const Vector2D<TYPE>& operator /=(const float mult)
	{
		x /= mult;
		y /= mult;
		return (*this);
	}

	Vector2D<TYPE> operator /(const float mult) const
	{
		Vector2D<TYPE> newVec;
		newVec.x = x / mult;
		newVec.y = y / mult;
		return newVec;
	}

	Vector2D& setToZero()
	{
		x = y = 0;
		return(*this);
	}

	//Set an angle in degrees
	void setAngle(float angle)
	{
		float mod = getModule();
		float i = DEGTORAD(angle);
		y = -mod * sin(i);
		x = mod * cos(i);

	}

	Vector2D& negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	bool isOpposite(const Vector2D v)
	{
		float a1 = getAngle();
		float a2 = v.getAngle();

		if (abs(a1 - a2) > 178 && abs(a1 - a2) < 182)
			return true;
		return false;
	}

	float getModule() const
	{
		return sqrt(x*x + y*y);
	}

	float getAngle() const
	{
		int y2 = (int)round(y);
		int x2 = (int)round(x);
		double angle = atan2(y2, x2);
		angle = RADTODEG(angle);
		if (angle > 0)
			angle -= 360;
		if (angle != 0)
			angle = -angle;
		return (float)angle;
	}

	Vector2D getNormal() const
	{
		float module = getModule();
		Vector2D vect;
		if (module != 0)
		{
			vect.x = x / module;
			vect.y = y / module;
		}
		return vect;
	}

	bool normalize()
	{
		float module = getModule();
		if (module != 0)
		{
			x /= module;
			y /= module;
			return true;
		}
		return false;
	}

};

#endif //__VECTOR2D_H__