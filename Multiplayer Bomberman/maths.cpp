#include "maths.h"

namespace math 
{
	Vector2::Vector2(void) : x(0), y(0)
	{
	}

	Vector2::Vector2(const Vector2& p) : x(p.x), y(p.y)
	{
	}

	Vector2::Vector2(float x_, float y_) : x(x_), y(y_)
	{
	}

	Vector2::~Vector2(void)
	{
	}

	void Vector2::operator=(const Vector2& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
	}

	bool Vector2::operator==(const Vector2 &rhs) const
	{
		return math::CloseEnough(x, rhs.x) && math::CloseEnough(y, rhs.y);
	}

	bool Vector2::operator!=(const Vector2 &rhs) const
	{
		return !(*this == rhs);
	}

	Vector2 &Vector2::operator+=(const Vector2 &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 &Vector2::operator-=(const Vector2 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 &Vector2::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2 &Vector2::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	Vector2 Vector2::operator+(const Vector2 &rhs) const
	{
		Vector2 tmp(*this);
		tmp += rhs;
		return tmp;
	}

	Vector2 Vector2::operator-(const Vector2 &rhs) const
	{
		Vector2 tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 Vector2::operator/(float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

    bool Vector2::LessThanX(const float x_) const
    {
        return x < x_;
    }

    bool Vector2::LessThanY(const float y_) const
    {
        return y < y_;
    }

	float Vector2::Dot( const Vector2& p, const Vector2& q ) const
	{
		return (p.x * q.x) + (p.y * q.y);
	}

	float Vector2::Distance( const Vector2& v1, const Vector2& v2 )
	{
		return sqrtf(DistanceSQ(v1, v2));
	}

	float Vector2::DistanceSQ( const Vector2& v1, const Vector2& v2 ) const
	{
		return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y));
	}

	float Vector2::Magnitude() const
	{
		return sqrtf((x * x) + (y * y));
	}

	float Vector2::MagnitudeSQ() const
	{
		return (x * x) + (y * y);
	}

	void Vector2::Normalise()
	{
		float inverse_mag = 1.0f / Magnitude();
		x *= inverse_mag;
		y *= inverse_mag;
	}

	void Vector2::Lerp( const Vector2& p, const Vector2& q, float t )
	{
		(*this) = p + (p - q) * t;
	}
}

