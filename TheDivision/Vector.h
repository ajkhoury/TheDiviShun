#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <math.h>

#define PI 3.14159265358979323846f
#define DEG2RAD(x)  ((float)(x) * (float)(PI / 180.f))
// MOVEMENT INFO
enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

inline bool IsFinite(const float& f)
{
	return ((*reinterpret_cast<unsigned __int32*>((char*)(&f)) & 0x7F800000) != 0x7F800000);
}

class Vector
{
public:
	// members
	float x, y, z;

	Vector() { x = y = z = 0.0f; }
	Vector(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	Vector(const Vector &v) { x = v.x; y = v.y; z = v.z; }

	float length() { return sqrtf(x*x + y*y + z*z); }
	void substract(Vector sub) { x -= sub.x; y -= sub.y; z -= sub.z; }
	float dotproduct(Vector dot) { return (x*dot.x + y*dot.y + z*dot.z); }
	void normalize() { float l = 1 / length(); x *= l; y *= l; z *= l; }
	float vectodegree(Vector to)
	{
		return ((180.0f / PI)*(asinf(dotproduct(to))));
	}

	Vector RotateX(Vector in, float angle)
	{
		float a, c, s;
		Vector out;
		a = (float)DEG2RAD(angle);
		c = (float)cos(a);
		s = (float)sin(a);
		out.x = in.x;
		out.y = c*in.y - s*in.z;
		out.z = s*in.y + c*in.z;
		return out;
	}

	Vector RotateY(Vector in, float angle)
	{
		float a, c, s;
		Vector out;
		a = (float)DEG2RAD(angle);
		c = (float)cos(a);
		s = (float)sin(a);
		out.x = c*in.x + s*in.z;
		out.y = in.y;
		out.z = -s*in.x + c*in.z;
		return out;
	}

	Vector RotateZ(Vector in, float angle)
	{
		float a, c, s;
		Vector out;
		a = (float)DEG2RAD(angle);
		c = (float)cos(a);
		s = (float)sin(a);
		out.x = c*in.x - s*in.y;
		out.y = s*in.x + c*in.y;
		out.z = in.z;
		return out;
	}

	Vector Forward(Vector angles)
	{
		Vector out;

		float	sp, sy, cp, cy;

		sy = sinf(DEG2RAD(angles[YAW]));
		cy = cosf(DEG2RAD(angles[YAW]));

		sp = sinf(DEG2RAD(angles[PITCH]));
		cp = cosf(DEG2RAD(angles[PITCH]));

		out.x = cp*cy;
		out.y = cp*sy;
		out.z = -sp;

		return out;
	}

	Vector Right(Vector angles)
	{
		Vector out;

		float	sr, sp, sy, cr, cp, cy;

		sy = sinf(DEG2RAD(angles[YAW]));
		cy = cosf(DEG2RAD(angles[YAW]));

		sp = sinf(DEG2RAD(angles[PITCH]));
		cp = cosf(DEG2RAD(angles[PITCH]));

		sr = sinf(DEG2RAD(angles[ROLL]));
		cr = cosf(DEG2RAD(angles[ROLL]));

		out.x = (-1 * (sr*sp*cy) + -1 * (cr*-sy));
		out.y = (-1 * (sr*sp*sy) + -1 * (cr*cy));
		out.z = (-1 * sr*cp);

		return out;
	}

	Vector Up(Vector angles)
	{
		Vector out;

		float	sr, sp, sy, cr, cp, cy;

		sy = sinf(DEG2RAD(angles[YAW]));
		cy = cosf(DEG2RAD(angles[YAW]));

		sp = sinf(DEG2RAD(angles[PITCH]));
		cp = cosf(DEG2RAD(angles[PITCH]));

		sr = sinf(DEG2RAD(angles[ROLL]));
		cr = cosf(DEG2RAD(angles[ROLL]));

		out.x = (cr*sp*cy + -sr*-sy);
		out.y = (cr*sp*sy + -sr*cy);
		out.z = cr*cp;

		return out;
	}

	float Distance(Vector in)
	{
		float deltax = in.x - x;
		float deltay = in.y - y;
		float deltaz = in.z - z;
		return sqrtf((deltax*deltax) + (deltay*deltay) + (deltaz*deltaz));
	}

	inline bool IsValid() const
	{
		return IsFinite(x) && IsFinite(y) && IsFinite(z);
	}

	void nullvec() { x = y = z = 0; }

	bool isNull() { return ((x == 0) && (y == 0) && (z == 0)); }

	void operator=(const float *farray) { x = farray[0]; y = farray[1]; z = farray[2]; }
	void operator=(const float &val) { x = y = z = val; }

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	Vector operator+(const Vector& add) const { return Vector(x + add.x, y + add.y, z + add.z); }
	void operator+=(const Vector& add) { x += add.x; y += add.y; z += add.z; }

	Vector operator-(const Vector& sub) const { return Vector(x - sub.x, y - sub.y, z - sub.z); }
	void operator-=(const Vector& sub) { x -= sub.x; y -= sub.y; z -= sub.z; }

	Vector operator*(const float mul)	const { return Vector(x*mul, y*mul, z*mul); }
	void operator*=(const float mul) { x *= mul; y *= mul; z *= mul; }

	Vector operator/(const float div) { return Vector(x / div, y / div, z / div); }
	Vector operator/(const float div)	const { return Vector(x / div, y / div, z / div); }
	void operator/=(const float div) { x /= div; y /= div; z /= div; }

	bool operator==(const Vector& eqal) { return ((x == eqal.x) && (y == eqal.y) && (z == eqal.z)); }
	bool operator!=(const Vector& eqal) { return ((x != eqal.x) && (y != eqal.y) && (z != eqal.z)); }

	bool operator>(const Vector& eqal) { return ((x > eqal.x) && (y > eqal.y) && (z > eqal.z)); }
	bool operator<(const Vector& eqal) { return ((x < eqal.x) && (y < eqal.y) && (z < eqal.z)); }

	bool operator>=(const Vector& eqal) { return ((x >= eqal.x) && (y >= eqal.y) && (z >= eqal.z)); }
	bool operator<=(const Vector& eqal) { return ((x <= eqal.x) && (y <= eqal.y) && (z <= eqal.z)); }
};

// Array access ---------------------------------------------------------------
inline float& Vector::operator[](int i)
{
	return ((float*)this)[i];
}
inline float Vector::operator[](int i) const
{
	return ((float*)this)[i];
}
//-----------------------------------------------------------------------------


#endif