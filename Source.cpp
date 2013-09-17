#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#include <GL\freeglut.h>
#include <GL\GL.h>
#include <iostream>
#include <fstream>
#include "WORLD.h"

using namespace std;

tile gergory;
unsigned int initSize[2] = {1,1};
world DAN(initSize);
double* mallColors;
double* mall;

void display(void)
{
	glClearColor(0,0,0.1,0);
	glutInitDisplayMode(GL_DEPTH|GL_FLOAT|GL_RGBA);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluOrtho2D(0, 500, 500, 0);

	//glColorPointer(3*DAN.getX()*DAN.getY(), GL_FLOAT, 0 , mallColors);
	//glVertexPointer(2*DAN.getX()*DAN.getY(), GL_INT, 0, mall);

	//glDrawArrays(GL_POINTS,0, 2*DAN.getX()*DAN.getY());
	glColor3f(1,1,1);
	glPointSize(10);
	glBegin(GL_POINTS);
	unsigned int pos[2];
	for(int i = 0; i < DAN.getX(); i++)
	{
		pos[0] = i;
		for(int j = 0; j < DAN.getY(); j++)
		{
			pos[1] = j;
			if(DAN.getTileCollision(DAN.checkTileMap(pos))) glColor3f(1,1,1);
			else glColor3f(1,0,0);
			glVertex2i(j*10,i*10);
		}
	}
	glEnd();

	glutPostRedisplay();
	glFlush();
}

void populateWorld(world map)
{
	int x = map.getX();
	int y = map.getY();
	mallColors = new double[3*x*y];
	mall = new double[3*x*y];
	unsigned int pos[2];
	for(int i = 0; i < x; i++)
	{
		pos[0] = i;
		for(int j = 0; j < y; j++)
		{
			pos[1] = j;
			if(map.checkTileMap(pos) == 0)
			{
				mallColors[3*(i + j*y)] = 0;
				mallColors[3*(i + j*y) + 1] = 0;
				mallColors[3*(i + j*y) + 2] = 1;
			}
			else
			{
				mallColors[3*(i + j*y)] = 1;
				mallColors[3*(i + j*y) + 1] = 1;
				mallColors[3*(i + j*y) + 2] = 1;
			}
			mall[3*(i + j*y)] = x/100;
			mall[3*(i + j*y) + 1] = y/100;
			mall[3*(i + j*y) + 2] = 0;
		}
	}
}

void reshape(int x, int y)
{
	//gluOrtho2D(0, x, 0, y);
}

void main(int argv, char* argc[])
{
	tile block;

	object newBlock;

	unsigned int size[] = {1,1};

	player greg;
	unsigned int meow[2] = {0,0};// = new unsigned int[2];
	cout << meow[0] << ' ' << meow[1] << endl;

	//DAN.changeTilePassthrough(1, true);
	//DAN.changeObjectPassthrough(0, true);

	size[0] = 30;
	size[1] = 30;

	block.changeDescription("HOORAY");
	block.changePassThrough(true);

	DAN.changeDimension(size);
	cout << DAN.getTileCollision(0) << endl;
	size[0] = 5;
	size[1] = 5;

	DAN.addTile(block);
	DAN.printLog();
	for(int j = 0; j < 2; j++)
	{
		for(int i = 0; i < 20; i++)
		{
			DAN.setTileLocation(size, 1);
			size[0]++;
		}
		size[1]++;
		size[0]-=20;
	}
	populateWorld(DAN);

	for(int i = 0; i < DAN.getX(); i++)
	{
		size[0] = i;
		for(int j = 0; j < DAN.getY(); j++)
		{
			size[1] = j;
			cout << (DAN.checkTileMap(size));
		}
		cout << endl;
	}

	glutInit(&argv, argc);
	glutInitWindowSize(500,500);
	glutCreateWindow("Pure Kleptomania");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

#endif