/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/20                                                           */
/************************************************************************/
#pragma once

#include <vector>
#include <string>
#include <GL/freeglut.h>

#include "Vector2.h"
#include "Vector3.h"

namespace bokken {
	class Terrain {
	private:
		int width, height;
		float middleWidth, middleHeight;
		float horizontalScale, verticalScale;

		int vertexNum;
		std::vector<float> terrainHeights;
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> textureCoords;
		std::vector<int> triangleStrip;

		Vector3 getVertex(int, int);
		Vector2 getTextureCoord(int, int);
		GLuint textureId;

	public:
		Terrain(void);
		void createHeightsFromImage(const std::string&);
		void createTexture(const std::string&);
		void initVertices(void);
		void createTriangleStrip(void);
		void draw(void);
		Vector2 getRandomPosition(void);
	};

}