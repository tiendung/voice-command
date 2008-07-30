/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/04                                                           */
/************************************************************************/
#pragma once

namespace bokken {

	/**
	* Vectors with two components (x, y).
	*/
	class Vector2
	{
	public:
		float x, y;
	public:
		Vector2(const float x, const float y);
		Vector2(const Vector2& other);
		~Vector2(void);

		/**
		* Set value for all two components
		* @param x : x component
		* @param y : y component
		*/
		void set(const float x, const float y);

		/**
		* add method
		* @param dx : added value to x component
		* @param dy : added value to y component
		*/
		void add(const float dx, const float dy);
	};
}