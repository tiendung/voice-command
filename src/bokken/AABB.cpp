/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
//contains definitions of float's maximum and minimum
#include <float.h>

#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>

#include "AABB.h"
#include "Frustum.h"

namespace bokken {

	AABB::AABB()
		:min_(Vector3(FLT_MAX, FLT_MAX, FLT_MAX))
		,max_(Vector3(FLT_MIN, FLT_MIN, FLT_MIN)) 
	{}

	void AABB::updateBox(const Vector3& vec) {
		if (vec.x < min_.x) min_.x = vec.x;
		if (vec.y < min_.y) min_.y = vec.y;
		if (vec.z < min_.z) min_.z = vec.z;
		if (vec.x > max_.x) max_.x = vec.x;
		if (vec.y > max_.y) max_.y = vec.y;
		if (vec.z > max_.z) max_.z = vec.z;
	}

	bool AABB::inFrustum(void) const {
		static Frustum frustum;
		frustum.refresh();
		return	frustum.inFrustum(min_.x, min_.y, min_.z) |
				frustum.inFrustum(min_.x, min_.y, max_.z) |
				frustum.inFrustum(min_.x, max_.y, min_.z) |
				frustum.inFrustum(min_.x, max_.y, max_.z) |
				frustum.inFrustum(max_.x, min_.y, min_.z) |
				frustum.inFrustum(max_.x, min_.y, max_.z) |
				frustum.inFrustum(max_.x, max_.y, min_.z) |
				frustum.inFrustum(max_.x, max_.y, max_.z);
		
	}

	void AABB::draw(void) const{
		//glColor3ub(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(min_.x, min_.y, min_.z);
		glVertex3f(min_.x, max_.y, min_.z);
		glVertex3f(max_.x, max_.y, min_.z);
		glVertex3f(max_.x, min_.y, min_.z);
		glEnd();
		
		glBegin(GL_LINE_LOOP);
		glVertex3f(min_.x, min_.y, max_.z);
		glVertex3f(min_.x, max_.y, max_.z);
		glVertex3f(max_.x, max_.y, max_.z);
		glVertex3f(max_.x, min_.y, max_.z);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(min_.x, min_.y, min_.z);
		glVertex3f(min_.x, min_.y, max_.z);

		glVertex3f(min_.x, max_.y, min_.z);
		glVertex3f(min_.x, max_.y, max_.z);

		glVertex3f(max_.x, max_.y, min_.z);
		glVertex3f(max_.x, max_.y, max_.z);

		glVertex3f(max_.x, min_.y, min_.z);
		glVertex3f(max_.x, min_.y, max_.z);
		glEnd();
	}
}