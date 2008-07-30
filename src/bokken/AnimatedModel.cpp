/************************************************************************/
/* This class encapsulate Md2.h and Md2.cpp functions                   */
/************************************************************************/
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/21                                                           */
/************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <corona.h>

#include "AnimatedModel.h"

using namespace std;
using namespace md2_model;

namespace bokken {
	const int AnimatedModel::LoopFrameNum = 6;
	bool AnimatedModel::enableDisplayingAabb = true;
	bool AnimatedModel::enableAnimating = true;
	bool AnimatedModel::enableFrustumCulling = true;
	int AnimatedModel::inFrustumNum = 0;
	int AnimatedModel::totalObjectNum = 0;

	AnimatedModel::AnimatedModel(void) 
		:md2_model(NULL)
		,angle(0)
		,position(Vector3(0,0,0))
		,name("NO_NAME")
	{
		totalObjectNum++;
		currentAct.startFrame = 0;
		currentAct.endFrame = 0;
	}

	AnimatedModel::~AnimatedModel(void) {
		if (md2_model != NULL) {
			md2_freeModel(md2_model);
			totalObjectNum--;
		}
	}
	
	void AnimatedModel::reset(void) {
		current_frame = currentAct.startFrame;
		current_subframe = 0;
		framesPassed = 0;
		preTime = glutGet(GLUT_ELAPSED_TIME);
	}

	void AnimatedModel::loadModel(const string& filename) {
		// load 3D information of the model
		name = filename;
		md2_model =	md2_readModel(filename.c_str());
		updateFrameAabbs();
		classifyActions();
		setAction("ALL");
	}

	void AnimatedModel::createTexture(const string& filename) {
		// load texture of the model
		corona::Image* image = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);
		glGenTextures(1, &Decal_Texture);
		glBindTexture(GL_TEXTURE_2D, Decal_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
		delete image;
	}
	
	void AnimatedModel::draw() {
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle, 0, 1, 0);
		// Scale animated models to a appropriate size
		glScalef(0.35f, 0.35f, 0.35f);
		if (!enableFrustumCulling || getCurrentAabb().inFrustum()) {
			inFrustumNum++;
			glBindTexture(GL_TEXTURE_2D, Decal_Texture);
			md2_drawModel(md2_model, current_frame, current_frame+1, (float)current_subframe/LoopFrameNum);
			if (enableDisplayingAabb)
				getCurrentAabb().draw();
		}
		glPopMatrix();
		
		if ( enableAnimating ) {
			int time = glutGet(GLUT_ELAPSED_TIME);
			// always go through 50 sub frames per second
			framesPassed += (time - preTime) / 20.0f;
			preTime = time;

			current_subframe += (int)floor(framesPassed);
			framesPassed -= floor(framesPassed);

			if (current_subframe >= LoopFrameNum ) {
				current_subframe = 0;
				current_frame++;
				if (current_frame == currentAct.endFrame) 
					current_frame = currentAct.startFrame;
			}
		} // end if ANIMATING

	}
	
	string AnimatedModel::getActionName(int frame) {
		string name="";
		char *p = md2_model->frames[frame].name;
		while ((*p < '0' || *p > '9') && p != 0) {
			name += *p;
			p++;
		}
		return name;
	}

	void AnimatedModel::classifyActions(void) {
		Action act;
		act.startFrame = 0;
		int frame;
		std::string name = getActionName(0);

		for (frame = 1; frame < getNumberOfFrames(); frame++) {
			string currName = getActionName(frame);
			if (currName != name) {
				act.endFrame = frame - 1;
				actions[name] = act;
				name = currName;
				act.startFrame = frame;
			}
		}
		// add last action
		act.endFrame = frame - 1;
		actions[name] = act;
		// add "ALL" action (including all frames)
		act.startFrame = 0;
		actions["ALL"] = act;
		
		// init actionNames
		actionNames.reserve(actions.size());
		std::map<string, Action>::iterator iter = actions.begin();
		for (; iter != actions.end(); iter++) {
			actionNames.push_back(iter->first);
		}
	}

	void AnimatedModel::setAction(const std::string& name) {
		currentAct = actions[name];
		reset();
	}

	void AnimatedModel::setAction(int id) {
		setAction(actionNames[id]);
	}

	size_t AnimatedModel::getNumberOfActions(void) {
		return actionNames.size();
	}

	int AnimatedModel::getNumberOfFrames(void) {
		return md2_model->header.numFrames;
	}

	AABB AnimatedModel::createAabbForFrame(int frameIndex)
	{
		AABB box;
		for (int i = 0; i < md2_model->header.numVertices; i++)
		{
			md2_triangleVertex_t *v = &md2_model->frames[frameIndex].vertices[i];
			box.updateBox(Vector3(v->vertex[0], v->vertex[1], v->vertex[2]));
		}
		return box;
	}

	void AnimatedModel::updateFrameAabbs(void) {
		frameAabbs.reserve(getNumberOfFrames());
		for (int i = 0; i < getNumberOfFrames(); i++) {
			frameAabbs.push_back(createAabbForFrame(i));
		}
	}

	const AABB& AnimatedModel::getCurrentAabb(void) {
		return frameAabbs[current_frame];
	}

	const Vector3& AnimatedModel::getPosition(void) {
		return position;
	}

	void AnimatedModel::setPosition(const Vector3& v) {
		position = v;
	}

	void AnimatedModel::setAngle(float f) {
		angle = f;
	}
}
