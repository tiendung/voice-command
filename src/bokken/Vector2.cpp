/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
#include "Vector2.h"

namespace bokken {

	Vector2::Vector2(const float fX, const float fY)
	:x(fX), y(fY)
	{
	}

	Vector2::Vector2(const Vector2& other)
	:x(other.x), y(other.y)
	{
	}

	Vector2::~Vector2(void)
	{
	}

	void Vector2::set(const float fX, const float fY) {
		x = fX;
		y = fY;
	}

	void Vector2::add(const float dx, const float dy) {
		x += dx;
		y += dy;
	}
}