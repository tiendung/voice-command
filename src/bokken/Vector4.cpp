/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/28                                                           */
/************************************************************************/
#include "Vector4.h"

#include <cmath>

namespace bokken {
		
	void normalizePlane(Vector4& v) {
		float mag = 0;
		for (int i = 0; i < 3; i++)
			mag += v[i]*v[i];
		
		mag = sqrt(mag);
		for (int i = 0; i < 4; i++)
			v[i] /= mag;
	}

}