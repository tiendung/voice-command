#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <GL/freeglut.h>

#include "bokken/Terrain.h"
#include "bokken/AnimatedModel.h"
#include "bokken/Vector3.h"
#include "ModelStack.h"

// Application specific structure used as shared memory
struct TSharedMemory {
	DWORD m_dwProcessId;      // Process ID from client
	CHAR m_cText[512];        // Text from client to server
};

HANDLE m_hExec;           // Client informs server
HANDLE m_hMap;            // Shared memory
TSharedMemory *m_pMsg;    // Pointer to shared memory object

#define DELTA_ANGLE 1.0f

char commandStr[255] = "Press Right Mouse Button to start voice command";

int screenwidth, screenheight;
float x_angle, y_angle;
bool show_frame, show_texture, near_view;
static float frameRate = 0.0f;
float posZ = 60.0f, posX = 0.0f, posY = 0.0f;

using namespace bokken;
using namespace std;

Terrain terrain;
AnimatedModel knight1, knight2, tris;
ModelStack models;

void InitializeGlut(int *argc, char *argv[]);
void Display(void);
void Keyboard(int key, int x, int y);
void initTerrainScene();
void calculateFrameRate(void);

void initSharedMem()
{
	m_hMap = ::CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,
		sizeof(TSharedMemory),
		"VoiceCalcSharedMem");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		m_hMap = ::OpenFileMapping(FILE_MAP_WRITE,FALSE,"VoiceCalcExec");
	} 
	m_pMsg = (TSharedMemory*)::MapViewOfFile(m_hMap,FILE_MAP_WRITE,0,0,sizeof(TSharedMemory));
	m_hExec = ::CreateEvent(NULL,FALSE,FALSE,"VoiceCalcExec");
}

void closeHvite()
{
	HANDLE HVite = NULL;
	HVite = ::OpenProcess( PROCESS_TERMINATE, FALSE,m_pMsg->m_dwProcessId);
	if (HVite != NULL) 
	{
		::TerminateProcess(HVite, 0);
	}
}
