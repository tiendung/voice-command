/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/

#include <assert.h>
#include "Matrix4x4.h"

namespace bokken {
	Matrix4x4::Matrix4x4() {
		for (int i = 0; i < 16; i++)
			operator[](i) = 0;
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& other) {
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				this->m[row][col] = other.m[row][col];
	}

	const Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 4; col++)
				this->m[row][col] = other.m[row][col];
		return *this;
	}

	Matrix4x4::Matrix4x4(const float* fArray) {
		for (int i = 0; i < 16; i++)
			this->operator[](i) = fArray[i];
	}

	float& Matrix4x4::operator [](int index) {
		assert(index >= 0 && index < 16);
		return m[index/4][index%4];
	}
	
	const Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) {
		Matrix4x4 result;
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				result.m[row][col] = 0;
				for (int k = 0; k < 4; k++) {
					result.m[row][col] += lhs.m[row][k] * rhs.m[k][col];
				}
			} // end for col
		} // end for row
		return result;
	}
}