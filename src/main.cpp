/************************************************************************
/* CS5243 Mini Project: Using voice command to control TRIS in A3 sence
/* Nguyen Tien Dung
/* HT055497N
/* 2007/03/29
/*
/************************************************************************
/* USAGE
/************************************************************************
/* For convenient, you can use only mouse to moving around the scene
/* ----------------------------------------------------------------------
/* 1) left-mouse-button-down + mouse-move to rotate scene
/* 2) right-mouse-button-down + mouse-move to move camera
/* 3) wheel-button-scrolling to zoom camera in and out
/* ----------------------------------------------------------------------
/* Buttons
/* ----------------------------------------------------------------------
/* F1: turn on/off AABB
/* F2: enable/disable frustum culling
/* F3: enable/disable animation
/* F8: add a knight
/* F9: remove the latest knight
/*
/* ----------------------------------------------------------------------
/* "Esc" to exit
/* "w/s" camera move up/down
/* "a/d" camera move left/right
/* "z/x" to zoom camera in and out
/* "n" to set view near/far
/* "f" to turn on/off show frame
/* "t" to turn on/off texture
/* "0, 1, 2, .. 9" to set tris action
************************************************************************/

#include "main.h"
#include "Input.h"


void printStr(int x, int y, const char* str) {
	glRasterPos2i(x, screenheight - y);
	for (size_t i=0; i < strlen(str); i++) 
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
}

void displaySystemInfor() {  
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, screenwidth, 0, screenheight);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();

	char str[255];
	sprintf_s(str, "AABB: %d | Frustum: %d | Animation: %d",
		AnimatedModel::enableDisplayingAabb, AnimatedModel::enableFrustumCulling, AnimatedModel::enableAnimating);
	printStr(10, 15, str);
	sprintf_s(str, "Frame Rate: %4.2f fps | Rendered Models: %d/%d",
		frameRate, AnimatedModel::inFrustumNum, AnimatedModel::totalObjectNum);
	printStr(10, 30, str);
  printStr(10, 45, commandStr);
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void checkHvite() {
	if (::WaitForSingleObject(m_hExec, 10) == WAIT_OBJECT_0) 
	{
		char str[1000];
		strcpy(str, m_pMsg->m_cText);
		if (strcmp(m_pMsg->m_cText,"READY") != 0)
		{
			closeHvite();

      char *p = str + strlen(str) - 1; while (*p != '#' && p != str) p--; if (*p == '#') *(p-1) = 0;
      p = str; while (*p != '#' && *p != 0) p++; if (*p == '#') p+=2;
      printf("Command = \"%s\"", p);
      sprintf_s(commandStr,"Command: %s", p);
      if (strcmp(p, "close") == 0)
        exit(0);
      tris.setAction(p);
		}
	}
}

void Display(void)
{
	checkHvite();
	glClearColor(0.5, 0.5, 0.5, 1);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(posX, posY, posZ, posX, posY, posZ-1, 0, 1, 0);
	glViewport(0, 0, screenwidth, screenheight);

	if (show_frame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glRotatef(x_angle, 1.0, 0.0, 0.0);
	glRotatef(y_angle, 0.0, 1.0, 0.0);

	if (show_texture)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);

	// DRAW YOUR TERRAIN HERE
	terrain.draw();

	// DRAW YOUR CHARACTERS HERE
	AnimatedModel::inFrustumNum = 0;
	knight1.draw();
	knight2.draw();
	tris.draw();
	models.draw();

	displaySystemInfor();

	glutSwapBuffers();
	calculateFrameRate();
}

void initTerrainScene() 
{
	printf("Init Terrain.. ");
	// GETTING THE HEIGHT MAP FROM an image
	terrain.createHeightsFromImage("..\\data\\heightmap.bmp");

    // GETTING THE TEXTURE MAP FROM an image
	terrain.createTexture("..\\data\\texture.jpg");

	// Create vertices and their texture coords
	terrain.initVertices();

	// Generate terrain's triangle strip
	terrain.createTriangleStrip();
	printf("Done\n");
}

void initAnimatedModels() {
	printf("Init Animated Models.. ");

	knight1.loadModel("..\\data\\knight.md2");
	knight1.createTexture("..\\data\\knight.pcx");
	knight1.setAction("stand");

	knight2.loadModel("..\\data\\knight.md2");
	knight2.createTexture("..\\data\\knight.pcx");
	knight2.setAction("flip");

	tris.loadModel("..\\data\\tris.md2");
	tris.createTexture("..\\data\\bauul.pcx");
	tris.setAction("wave");
	
	// Set positions and angles
	knight1.setPosition(Vector3(30, 10, 0));
	knight1.setAngle(-45);
	
	knight2.setPosition(Vector3(-5, 10, 30));
	knight2.setAngle(-60);

	tris.setPosition(Vector3(-5, 10, -30));
	tris.setAngle(-30);

	printf("Done\n");
}

void InitializeGlut(int *argc, char *argv[])
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenwidth, screenheight);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboardFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutMouseWheelFunc(mouseWheelFunc);
}

void calculateFrameRate(void) {
	static int preTime = glutGet(GLUT_ELAPSED_TIME);
	static int frame = 0;

	frame++;
	int time = glutGet(GLUT_ELAPSED_TIME);
	if (time - preTime > 2000) {
		frameRate = frame*1000.0f / (time - preTime);
		preTime = time;
		frame = 0;
	}
}

int main(int argc, char *argv[])
{
	initSharedMem();
	screenheight = 600;
	screenwidth  = 800;
	InitializeGlut(&argc, argv);
	initTerrainScene();
	initAnimatedModels();
	x_angle = 90.0f;
	y_angle = 0.0f;
	show_frame = false;
	show_texture = true;
	near_view = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, 1.0f, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
	
	return 0;
}