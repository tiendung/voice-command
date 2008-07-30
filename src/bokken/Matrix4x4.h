/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/
#pragma once

#include "Vector4.h"

namespace bokken {

	class Matrix4x4 {
	private:
		float m[4][4];
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& other);
		Matrix4x4(const float* fArray);
		const Matrix4x4& operator=(const Matrix4x4& other);
		float& operator[](int index);
		friend const Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
		const Vector4 getRow(int row)
		{return Vector4(m[row][0],m[row][1],m[row][2],m[row][3]);};
		const Vector4 getColumn(int col)
		{return Vector4(m[0][col],m[1][col],m[2][col],m[3][col]);};
	};
}