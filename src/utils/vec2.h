#pragma once
#include <iostream>

struct Vector2
{
	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 right;
	static const Vector2 up;

	float x, y;

	Vector2() : x(0.f), y(0.f) {}
	Vector2(float v) : x(v), y(v) {}
	Vector2(float x, float y) : x(x), y(y) {};

	Vector2 operator+() const { return Vector2(x, y); }
	Vector2 operator-() const { return Vector2(-x, -y); }

	friend Vector2 operator*(const Vector2& lhs, const float& rhs) { return Vector2(lhs.x * rhs, lhs.y * rhs); }
	friend Vector2 operator*(const float& lhs, const Vector2& rhs) { return Vector2(rhs.x * lhs, rhs.y * lhs); }
	Vector2 operator+(Vector2& r) const { return Vector2(x + r.x, y + r.y); }
	Vector2 operator-(Vector2& r) const { return Vector2(x - r.x, y - r.y); }
	Vector2 operator/(float v) const { return Vector2(x / v, y / v); }

	Vector2 operator+=(const Vector2& r) { x += r.x; y += r.y; return *this; }
	Vector2 operator-=(const Vector2& r) { x -= r.x; y -= r.y; return *this; }
	Vector2& operator*=(float v) { x *= v; y *= v; return *this; }
	Vector2& operator/=(float v) { x /= v; y /= v; return *this; }
	friend bool operator==(const Vector2& l, const Vector2& r) { return l.x == r.x && l.y == r.y; }
	friend bool operator!=(const Vector2& l, const Vector2& r) { return l.x != r.x || l.y != r.y; }
	friend std::ostream& operator<<(std::ostream& os, const Vector2& v) { os << "(" << v.x << ", " << v.y << ")"; return os; }
	static float magnitude(const Vector2& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}
	static Vector2& normalize(Vector2& v)
	{
		float mag = Vector2::magnitude(v);
		Vector2 temp = v / mag;
		return temp;
	}
};

const Vector2 Vector2::zero(0.f, 0.f);
const Vector2 Vector2::one(1.f, 1.f);
const Vector2 Vector2::right(1.f, 0.f);
const Vector2 Vector2::up(0.f, 1.f);