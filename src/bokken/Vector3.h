/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
#pragma once

namespace bokken {
	/**
	* Vectors with three components (x, y, z).
	*/
	class Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3();
		Vector3(const float, const float, const float);
		Vector3(const Vector3&);
		const Vector3& operator=(const Vector3& rhs);
		~Vector3(void);

		/**
		* Set value for all three components
		* @param x : x component
		* @param y : y component
		* @param z : z component 
		*/
		void set(const float x, const float y, const float z);

		/**
		* add method
		* @param dx : added value to x component
		* @param dy : added value to y component
		* @param dz : added value to z component 
		*/
		void add(const float dx, const float dy, const float dz);
		
		const float magnitude(void);
		void normalize(void);
		/** Cross product */
		friend const Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
		friend const Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
		friend const Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
		friend const Vector3 operator/(const Vector3& lhs, const float rhs);
		const Vector3& operator*=(const float rhs);
		const Vector3& operator+=(const Vector3& rhs);
	};

	// Utility functions
	Vector3 createNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
}