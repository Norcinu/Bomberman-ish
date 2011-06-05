#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "maths.h"

#pragma warning(disable:4244)

namespace rec 
{
class Rectangle
{
public:
	Rectangle() : left(0), right(32), bottom(32), top(0)
	{
	}

	Rectangle(int l, int r, int b, int t) : left(l), right(r),
		bottom(b), top(t)
	{
	}

	Rectangle(const Rectangle& copy) : left(copy.left), right(copy.right),
		bottom(copy.bottom), top(copy.top)
	{
	}

	const int Width() const { return left - right; }
	const int Height() const { return bottom - top; }

	void Clip(const Rectangle& screenRec, math::Vector2& v)
	{
		left += v.x;
		right += v.x;
		top += v.y;
		bottom += v.y;

		if ( left < screenRec.left )
			left = screenRec.left;
		if ( right > screenRec.right )
			right = screenRec.right;
		if ( top < screenRec.top )
			top = screenRec.top;
		if ( bottom > screenRec.bottom )
			bottom = screenRec.bottom;

		left -= v.x;
		right -= v.x;
		top -= v.y;
		bottom -= v.y;
	}

	bool CompletelyContains(const int x, const int y, const Rectangle& other) const
	{		
		if (x > 0 && x < right - other.Width() && y > 0 && y < bottom - other.Height())
			return true;
		else
			return false;
	}

	bool CompletelyOutside(const int x, const int y, const Rectangle& other) const
	{
		if (x > right)
			return true;
		if (y > bottom)
			return true;
		if (x < left - other.Width())
			return true;
		if (y < top - other.Height())
			return true;

		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const rec::Rectangle& rhs)
	{
		return os << rhs.left << " " << rhs.right << " " << rhs.top << " " << rhs.bottom;
	}

	friend std::istream& operator>>(std::istream& is, rec::Rectangle& rhs)
	{
		return is >> rhs.left >> rhs.right >> rhs.top >> rhs.bottom;
	}

	int left, right, bottom, top;
};

}

#endif
