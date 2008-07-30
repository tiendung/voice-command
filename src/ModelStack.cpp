/************************************************************************/
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/26                                                           */
/************************************************************************/
#include <gl/freeglut.h>
#include "ModelStack.h"
#include <stdlib.h>

using namespace bokken;
using namespace std;

void ModelStack::push(const AnimatedModel& model, const Vector3& v) {
	models.push_back(model);
	AnimatedModel::totalObjectNum++;
	AnimatedModel& m = models.back();
	m.loadModel(m.getName());
	m.setPosition(v);
	m.setAngle( 360.0f*rand()/RAND_MAX );
	int actionId = (int)(models.back().getNumberOfActions()*rand()/RAND_MAX);
	m.setAction( actionId );
}

void ModelStack::pop(void) {
	if (models.size() > 0)
		models.pop_back();
}

void ModelStack::draw(void) {
	list<AnimatedModel>::iterator iter = models.begin();
	for (; iter != models.end(); iter++) {
		iter->draw();
	}
}