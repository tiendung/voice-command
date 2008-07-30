/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/
#pragma once

namespace bokken {
	class Vector4 {
	public:
		float v[4];

		Vector4(void){};
		const Vector4& operator=(const Vector4& other)
		{v[0]=other.v[0];v[1]=other.v[1];v[2]=other.v[2];v[3]=other.v[3]; return*this;};
		
		Vector4(float f0, float f1, float f2, float f3)
		{v[0]=f0; v[1]=f1; v[2]=f2; v[3]=f3;};

		float& operator[](int index) {return v[index];};
		
		Vector4(const float fArray[4])
		{v[0]=fArray[0]; v[1]=fArray[1]; v[2]=fArray[2]; v[3]=fArray[3];};
		
		friend const Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
		{return Vector4(lhs.v[0]-rhs.v[0],lhs.v[1]-rhs.v[1],lhs.v[2]-rhs.v[2],lhs.v[3]-rhs.v[3]);};

		friend const Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
		{return Vector4(lhs.v[0]+rhs.v[0],lhs.v[1]+rhs.v[1],lhs.v[2]+rhs.v[2],lhs.v[3]+rhs.v[3]);};

	};

	void normalizePlane(Vector4& plane);
}