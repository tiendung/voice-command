/************************************************************************/
/* Wrap in md2_model namespace
/* Modified by Nguyen Tien Dung
/* 2007/01/29
/************************************************************************/
/*/
//                 MD2 Viewer (c) 1999 by Mete Ciragan
//
// file:           md2.h
// last modified:  Apr 28 1999, Mete Ciragan
// copyright:      The programs and associated files contained in this
//                 distribution were developed by Mete Ciragan. The programs
//                 are not in the public domain, but they are freely
//                 distributable without licensing fees. These programs are
//                 provided without guarantee or warrantee expressed or
//                 implied.
//
// version:        1.4
//
// email:          mete@swissquake.ch
// web:            http://www.swissquake.ch/chumbalum-soft/
/*/
#ifndef INCLUDED_MD2
#define INCLUDED_MD2

namespace md2_model {

#ifndef byte
	typedef unsigned char byte;
#endif /* byte */

#define MD2_MAX_TRIANGLES		4096
#define MD2_MAX_VERTICES		2048
#define MD2_MAX_TEXCOORDS		2048
#define MD2_MAX_FRAMES			512
#define MD2_MAX_SKINS			32
#define MD2_MAX_FRAMESIZE		(MD2_MAX_VERTICES * 4 + 128)



struct md2_header_t
{ 
   int magic; 
   int version; 
   int skinWidth; 
   int skinHeight; 
   int frameSize; 
   int numSkins; 
   int numVertices; 
   int numTexCoords; 
   int numTriangles; 
   int numGlCommands; 
   int numFrames; 
   int offsetSkins; 
   int offsetTexCoords; 
   int offsetTriangles; 
   int offsetFrames; 
   int offsetGlCommands; 
   int offsetEnd; 
};

struct md2_alias_triangleVertex_t
{
   byte vertex[3];
   byte lightNormalIndex;
};

struct md2_triangleVertex_t
{
   float vertex[3];
   float normal[3];
   //byte lightNormalIndex;
};

struct md2_triangle_t
{
   short vertexIndices[3];
   short textureIndices[3];
};

struct md2_textureCoordinate_t
{
   short s, t;
};

struct md2_alias_frame_t
{
   float scale[3];
   float translate[3];
   char name[16];
   md2_alias_triangleVertex_t alias_vertices[1];
};

struct md2_frame_t
{
   char name[16];
   md2_triangleVertex_t *vertices;
};

typedef char md2_skin_t[64];

struct md2_glCommandVertex_t
{
   float s, t;
   int vertexIndex;
};

struct md2_model_t
{
	md2_header_t			header;
	md2_skin_t				*skins;
	md2_textureCoordinate_t	*texCoords;
	md2_triangle_t			*triangles;
	md2_frame_t				*frames;
	int						*glCommandBuffer;
};



#ifdef __cplusplus
extern "C" {
#endif

md2_model_t *md2_readModel (const char *filename);
void md2_freeModel (md2_model_t *model);
void md2_setStyle (int glcmds, int interp);
void md2_getBoundingBox (md2_model_t *model, float *minmax);
void md2_drawModel (md2_model_t *model, int frame1, int frame2, float pol);
void md2_generateLightNormals (md2_model_t *model);
int md2_getAnimationCount (md2_model_t *model);
const char *md2_getAnimationName (md2_model_t *model, int animation);
void md2_getAnimationFrames (md2_model_t *model, int animation, int *startFrame, int *endFrame);
void md2_printModelInfo(md2_model_t *model);


#ifdef __cplusplus
}
#endif

}

#endif /* INCLUDED_MD2 */
