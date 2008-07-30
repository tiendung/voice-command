/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
#include "Vector3.h"

namespace bokken {

	Vector3::Vector3()
		/* [Effective C++] 
		Item 4: make sure that objects are initialized before they're used */
		:x(0),y(0),z(0) 
	{}

	Vector3::Vector3(const float fX, const float fY, const float fZ)
		:x(fX), y(fY), z(fZ)
	{}

	/*[Effective C++] remember copy constructor */
	Vector3::Vector3(const Vector3& other)
	:x(other.x), y(other.y), z(other.z)
	{}
	
	/*[Effective C++] remember copy assigment operator */
	const Vector3& Vector3::operator=(const Vector3& rhs) {
		x = rhs.x; 
		y = rhs.y; 
		z = rhs.z;
		return *this;
	}

	Vector3::~Vector3(void){
	}

	void Vector3::set(const float fX, const float fY, const float fZ) {
		x = fX;
		y = fY;
		z = fZ;
	}

	void Vector3::add(const float dx, const float dy, const float dz) {
		x += dx;
		y += dy;
		z += dz;
	}

	/*[Effective C++]
	Item 03: use const whenever possible (remember if (a*b=c) mistake)
	Item 21: don't try to return a reference when you must return an object 
	*/
	const Vector3 operator*(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(	lhs.y*rhs.z - lhs.z*rhs.y, 
						lhs.z*rhs.x - lhs.x*rhs.z, 
						lhs.x*rhs.y - lhs.y*rhs.x);
	}

	const Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(	lhs.x - rhs.x, 
						lhs.y - rhs.y, 
						lhs.z - rhs.z);
	}

	const Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
		return Vector3(	lhs.x + rhs.x, 
						lhs.y + rhs.y, 
						lhs.z + rhs.z);
	}

	const Vector3 operator/(const Vector3& lhs, const float rhs) {
		return Vector3(	lhs.x / rhs,
						lhs.y / rhs,
						lhs.z / rhs);
	}

	/*[Effective C++]
	Item 20: prefer pass-by-ref-to-const to pass-by-value
		but not for primative type (int, float, bool ...)*/
	const Vector3& Vector3::operator+=(const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	const Vector3& Vector3::operator*=(const float rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	const float Vector3::magnitude(void) {
		return x*x+y*y+z*z;
	}

	void Vector3::normalize(void) {
		float mag = magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
	}

	// Utility functions
	Vector3 createNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
		return( v3 - v2 ) * ( v1 - v1 );
	}
}