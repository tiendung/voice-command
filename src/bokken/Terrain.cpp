/************************************************************************/
/* Bokken Game Engine                                                   */
/* Written by Nguyen Tien Dung                                          */
/* dungtn@comp.nus.edu.sg                                               */
/* 2007/01/20                                                           */
/************************************************************************/
#include "Terrain.h"
#include <corona.h>
#include <gl/freeglut.h>

using namespace bokken;
using namespace std;

Terrain::Terrain(void) {
	horizontalScale = 1.0f;
	verticalScale = 30.0f;

}
void Terrain::createHeightsFromImage(const string& filename) {
	corona::Image* heightImage = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);

	width = heightImage->getWidth();
	height = heightImage->getHeight();

	middleWidth = width / 2.0f;
	middleHeight = height / 2.0f;

	terrainHeights.reserve(width*height);

	GLubyte *pixels = (GLubyte *)heightImage->getPixels();

	for (int index = 0; index < width * height; index++) {
		int colorIndex = 3*index;
		GLubyte R = *(pixels + colorIndex);
		// for gray image R=G=B so we can use only one of these three values
		float pointHeight = R / 255.0f; 
		terrainHeights.push_back(pointHeight);
	}

	delete heightImage;
}

void Terrain::createTexture(const std::string& filename) {
	corona::Image* textureImage = corona::OpenImage(filename.c_str(), corona::PF_R8G8B8);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage->getWidth(), textureImage->getHeight(), 0, 
		GL_RGB, GL_UNSIGNED_BYTE, textureImage->getPixels());

	// delete image after use it
	delete textureImage;
}

Vector3 Terrain::getVertex(int iw, int ih) {
	int index = (iw + ih*width);
	float y = terrainHeights[index] * verticalScale;
	float x = (iw - middleWidth) * horizontalScale;
	float z = (ih - middleHeight) * horizontalScale;
	return Vector3(x, y, z);
}

Vector2 Terrain::getTextureCoord(int iw, int ih) {
	return Vector2( iw / (width-1.0f), ih / (height-1.0f) );
}

void Terrain::initVertices(void) {
	vertexNum = width * height;
	vertices.reserve( vertexNum );
	normals.reserve( vertexNum );
	textureCoords.reserve( vertexNum );
	for (int iw = 0; iw < width; iw++) {
		for (int ih = 0; ih < height; ih++) {
			vertices.push_back( getVertex(iw, ih) );
			textureCoords.push_back( getTextureCoord(iw, ih) );
			normals.push_back( Vector3(0,0,0) );
		}
	}
}

void Terrain::createTriangleStrip(void) {
	int	vertexIndex = 0;
	triangleStrip.reserve(2*width*height);

	for (int iw = 0; iw < width - 1; iw++) {
		if (iw % 2 == 0) {
			vertexIndex = iw * height;
			int max = vertexIndex + height;
			
			for (int count = 0; count < 2*height; count++) {
				triangleStrip.push_back(vertexIndex);
				if (vertexIndex < max) vertexIndex = vertexIndex + height;
								  else vertexIndex = vertexIndex - height + 1;
			}
		} // end if
		else {
			int max = vertexIndex + height;
			vertexIndex = max - 1;

			for (int count = 0; count < 2*height; count++) {
				triangleStrip.push_back(vertexIndex);
				if (vertexIndex < max) vertexIndex = vertexIndex + height;
								  else vertexIndex = vertexIndex - height - 1;
			}
		} // end else
	} // end for
}

void Terrain::draw(void) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLE_STRIP);
	for (size_t i = 0; i < triangleStrip.size(); i++) {
		int id = triangleStrip[i];
		glTexCoord2f( textureCoords[id].x, textureCoords[id].y);
		glVertex3f( vertices[id].x, vertices[id].y, vertices[id].z);
	}
	glEnd();
}

float random() {
	return (RAND_MAX / 2.0f - rand() ) / RAND_MAX;
}

Vector2 Terrain::getRandomPosition(void) {
	const int d = 50;
	float x =  (width-d)*horizontalScale*random();
	float z = (height-d)*horizontalScale*random();
	return Vector2(x, z);
}