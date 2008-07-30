/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/
#include "Frustum.h"
#include "Matrix4x4.h"

#include <gl/freeglut.h>

namespace bokken {
	enum FrustumSide {Right=0, Left, Bottom, Top, Back, Front};
	enum PlaneInfor {X=0, Y, Z, Distance};

	void Frustum::refresh(void) {
		static float fArray[16];
		glGetFloatv(GL_PROJECTION_MATRIX, fArray);
		Matrix4x4 projection(fArray);
		glGetFloatv(GL_MODELVIEW_MATRIX,  fArray);
		Matrix4x4 modelView(fArray);
		Matrix4x4 clip = modelView * projection;

		planes_ [ Right  ] = clip.getColumn(3) - clip.getColumn(0);
		planes_ [ Left   ] = clip.getColumn(3) + clip.getColumn(0);
		planes_ [ Bottom ] = clip.getColumn(3) + clip.getColumn(1);
		planes_ [ Top    ] = clip.getColumn(3) - clip.getColumn(1);
		planes_ [ Back   ] = clip.getColumn(3) - clip.getColumn(2);
		planes_ [ Front  ] = clip.getColumn(3) + clip.getColumn(2);

		for (int i = Right; i <= Front; i++) normalizePlane(planes_[i]);
	}


	bool Frustum::inFrustum(const Vector3& point) {
		for (int i = Right; i <= Front; i++)
			if ( distance(planes_[i], point) <= 0 ) {
				return false;
			}
		return true;
	}

	float distance(const Vector4& plane, const Vector3& point) {
		return  plane.v[X]*point.x + plane.v[Y]*point.y + plane.v[Z]*point.z + plane.v[Distance];
	}

}