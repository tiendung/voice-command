/************************************************************************/
/* This class encapsulate Md2.h and Md2.cpp functions                   */
/************************************************************************/
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/21                                                           */
/************************************************************************/
#pragma once

#include <string>
#include <map>
#include <vector>
#include <GL/freeglut.h>
#include "../MD2 Model/Md2.h"
#include "AABB.h"

namespace bokken {

	struct Action {
		int startFrame;
		int endFrame;
	};

	class AnimatedModel {
	private:
		static const int LoopFrameNum;

		std::string name;
		GLuint Decal_Texture;
		md2_model::md2_model_t* md2_model;
		float model_center[3], model_radius;
		int current_frame, current_subframe;
		float framesPassed;
		int preTime;

		Action currentAct;		
		std::map<std::string, Action> actions;
		std::vector<std::string> actionNames;

		std::vector<AABB> frameAabbs;
		Vector3 position;
		float angle;

		std::string getActionName(int frame);
		void classifyActions(void);
		void reset(void);
		AABB createAabbForFrame(int frameIndex);
		void updateFrameAabbs(void);
	public:
		static bool enableDisplayingAabb;
		static bool enableAnimating;
		static bool enableFrustumCulling;
		static int inFrustumNum;
		static int totalObjectNum;

		static void switchAabbOption(void){enableDisplayingAabb=!enableDisplayingAabb;};
		static void switchAnimatingOption(void){enableAnimating=!enableAnimating;};
		static void switchFrustumOption(void){enableFrustumCulling=!enableFrustumCulling;};

		AnimatedModel(void);
		~AnimatedModel(void);

		void setAction(const std::string& name);
		void setAction(int id);
		size_t getNumberOfActions(void);
		int getNumberOfFrames(void);
		void loadModel(const std::string& filename);
		void createTexture(const std::string& filename);
		const AABB& getCurrentAabb(void);
		const Vector3& getPosition(void);
		void setPosition(const Vector3& position);
		void setAngle(float angle);
		void draw(void);
		const std::string& getName(void) {return name;};

	};
}
