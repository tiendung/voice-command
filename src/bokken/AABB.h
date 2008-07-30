/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
#pragma once
#include "Vector3.h"

namespace bokken {

	/**
	* Axis Aligned Bounding Box
	*/
	class AABB {
	private:
		/** Minimum Vector3 */
		Vector3 min_;
		/** Maximum Vector3 */
		Vector3 max_;
	public:
		AABB();

		/**
		* Generate the bounding box around
		* @param vector - a Vector3 object
		*/
		void updateBox(const Vector3& vector);
		void draw(void) const;
		bool inFrustum(void) const;
	};
}