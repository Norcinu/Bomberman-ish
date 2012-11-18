#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace math
{
	const float PI = 3.141f;
	const float HALF_PI = PI / 2.0f;
	const float QUARTER_PI = PI / 4.0f;
	const float TWO_PI = PI * 2.0f;
	const float EPSILON = 1e-6f;

	static bool CloseEnough(float f1, float f2)
	{
		// Determines whether the two floating-point values f1 and f2 are
		// close enough together that they can be considered equal.
		return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	static long FloatToLong(float f)
	{
		// Converts a floating point number into an integer.
		// Fractional values are truncated as in ANSI C.
		// About 5 to 6 times faster than a standard typecast to an integer.
		long fpBits = *reinterpret_cast<const long*>(&f);
		long shift = 23 - (((fpBits & 0x7fffffff) >> 23) - 127);
		long result = ((fpBits & 0x7fffff) | (1 << 23)) >> shift;

		result = (result ^ (fpBits >> 31)) - (fpBits >> 31);
		result &= ~((((fpBits & 0x7fffffff) >> 23) - 127) >> 31);

		return result;
	}

	static bool IsPower2(int x)
	{
		return ((x > 0) && ((x & (x - 1)) == 0));
	}

	template <typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		// Performs a linear interpolation.
		//  P(t) = (1 - t)a + tb
		//       = a + t(b - a)
		//
		//  where
		//  t in range [0,1]

		return a + (b - a) * t;
	}

	static int NextMultipleOf(int multiple, int value)
	{
		// Returns the closest multiple of value that isn't less than value.
		return multiple * ((value + (multiple - 1)) / multiple);
	}

	static float DegreesToRadians(float degrees)
	{
		return (degrees * PI) / 180.0f;
	}

	static float RadiansToDegrees(float radians)
	{
		return (radians * 180.0f) / PI;
	}

	static float Random(float min, float max)
	{
		return min + (max - min)
			* (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	}

	template< typename T >
	static T Clamp(const T& x, const T& min, const T& max)
	{
		return x < min ? min : x > max ? max : x;
	}

	// end of namespace
	
	// Vector 2
	class Vector2
	{
	public:
		Vector2(void);
		Vector2(float x_, float y_);
		Vector2(const Vector2& p);
		
		~Vector2(void);
		
		float x;
		float y;
		
		float Dot(const Vector2& p, const Vector2& q) const;
		float Distance(const Vector2& v1, const Vector2& v2);
		float DistanceSQ(const Vector2& v1, const Vector2& v2) const;
		
		float Magnitude() const;
		float MagnitudeSQ() const;
		
		void Lerp(const Vector2& p, const Vector2& q, float t);
		//Vector2 Lerp(const Vector2& p, const Vector2& q, float t);
		void Normalise();

		void operator=(const Vector2& rhs);

		bool operator==(const Vector2& rhs) const;
		bool operator!=(const Vector2& rhs) const;
		
		Vector2& operator+=(const Vector2 &rhs);
		Vector2& operator-=(const Vector2 &rhs);
		Vector2& operator*=(float scalar);
		Vector2& operator/=(float scalar);

		Vector2 operator+(const Vector2 &rhs) const;
		Vector2 operator-(const Vector2 &rhs) const;
		Vector2 operator*(float scalar) const;
		Vector2 operator/(float scalar) const;
        
        bool LessThanX(const float x_) const;
        bool LessThanY(const float y_) const;

		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
		{
			return os << vec.x << " " << vec.y;
		}

		friend std::istream& operator>>(std::istream& is, Vector2& vec)
		{
			return is >> vec.x >> vec.y;
		}

	}; // end of Vector2

	static Vector2 MakeUnit( Vector2& vec )
	{
		float x = fabs(vec.x);
		float y = fabs(vec.y);
		float p = (x + y) * 100;

		x = (vec.x / p) * 100;
		y = (vec.y / p) * 100;

		return math::Vector2(x, y);
	}

	static float CalcDist(const Vector2& lhs, const Vector2& rhs)
	{
		return sqrt((lhs.x-rhs.x)*(lhs.x-rhs.x)+(lhs.y-rhs.y)*(lhs.y-rhs.y));
	}

	static float CalcDistSquared(const Vector2& lhs, const Vector2& rhs)
	{
		return ((lhs.x-rhs.x)*(lhs.x-rhs.x))+((lhs.y-rhs.y)*(lhs.y-rhs.y));
	}
} // end of namespace math

#endif
