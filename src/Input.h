/************************************************************************/
/* KEYBOARD FUNCTIONS                                                   */
/************************************************************************/
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'z': 
			{
				posZ -= 3;
				break;
			}
		case 'x': 
			{
				posZ += 3;
				break;
			}
		case 'a': 
			{
				posX -= 3;
				break;
			}
		case 'd': 
			{
				posX += 3;
				break;
			}
		case 'w': 
			{
				posY += 3;
				break;
			}
		case 's': 
			{
				posY -= 3;
				break;
  			}
		case 'f': 
			{
				show_frame = !show_frame;
				break;
			}
		case 'n': 
			{
				near_view = !near_view;
				if (near_view) {
					posX = 0; posY = 0; posZ = 60;
				}
				else {
					posX = 0; posY = 0; posZ = 200;
				}
				break;
			}
		case 't': 
			{
				show_texture = !show_texture;
				break;
			}
		case 27: 
			{
				//ESC button
				exit(0);
				break;
			}
		default:
			break;
	}

	if ('0' <= key && key <= '9') {
		tris.setAction(key - '0');
	}
}

void specialKeyboardFunc(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1: { 
			AnimatedModel::switchAabbOption();
			break;
		}
		case GLUT_KEY_F2: { 
			AnimatedModel::switchFrustumOption();
			break;
		}
		case GLUT_KEY_F3: { 
			AnimatedModel::switchAnimatingOption();
			break;
		}
		case GLUT_KEY_F8: {
			Vector2 terrainPos = terrain.getRandomPosition();
			models.push(knight1, Vector3(terrainPos.x, 10,terrainPos.y));
			break;
		}
		case GLUT_KEY_F9: {
			models.pop();
		}
		default:
			break;
	}
}
/************************************************************************/
/* MOUSE FUNCTIONS                                                      */
/************************************************************************/
int mW, mH;
int mButton, mX, mY;

void mouseFunc(int button, int state, int x, int y) {
	static bool doit = true;
	mButton = button;
	mX = x;
	mY = y;
	if (button == GLUT_RIGHT_BUTTON) {
		doit = !doit;
		if (doit) {
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			::WinExec("../recognizer/HVite -H ../recognizer/macros -H ../recognizer/hmmdefs -C ../recognizer/config -w ../recognizer/wdnet_cmd ../recognizer/dict ../recognizer/hmmlist", SW_HIDE);
      sprintf_s(commandStr, "Please speak one command: \"jump, pain, point, salute, stand, close\"");
		}
	}
	if (button == GLUT_LEFT_BUTTON) closeHvite();
}

void mouseMotionFunc(int x, int y) {
	int dx = (x - mX);
	int dy = (y - mY);
	mX = x;
	mY = y;

	switch(mButton) {
		case GLUT_LEFT_BUTTON: 
		{
			y_angle += dx/3.0f;
			x_angle += dy/3.0f;
			break; 
		}

		case GLUT_RIGHT_BUTTON: 
			{
				posX -= dx/3.0f;
				posY += dy/3.0f;
				break; 
			}
	}
}
void mouseWheelFunc(int wheel, int direction, int x, int y) {
	posZ += direction*5;
}
