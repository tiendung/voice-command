/************************************************************************/
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/26                                                           */
/************************************************************************/
#pragma once

#include "bokken/AnimatedModel.h"
#include <list>

class ModelStack {
private:
	std::list<bokken::AnimatedModel> models;
public:
	void push(const bokken::AnimatedModel&, const bokken::Vector3&);
	void pop(void);
	void draw(void);
};
