/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/

#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace bokken {
	class Frustum {
	private:
		Vector4 planes_[6];
	public:
		Frustum(void){};
		void refresh(void);
		bool inFrustum(const Vector3& point);
		bool inFrustum(float x, float y, float z)
		{return inFrustum( Vector3(x, y, z) ); };
	};

	float distance(const Vector4& plane, const Vector3& point);
}