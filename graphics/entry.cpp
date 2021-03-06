
//	"entry.cpp" -*- C++ -*-
//	Created on: 5 March 2016
//	Definitions of entry functions to GLUT.
//
//	Copyright (C) 2016  Geoffrey Tang.
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "graphics/entry.h"

#include "physics/config.h"
#include "native/keyboard.h"

extern	ConfigType	GameConfig;

void graphicsInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); /* sky blue background */
//	Enable 2D textures
	glEnable(GL_TEXTURE_2D);
//	Alpha textures are enabled
//	Thanks to http://stackoverflow.com
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	After doing this, textures wouldn't look blurry even if it's small
//	Thanks to http://stackoverflow.com (again)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	Using Cartesian system
	glMatrixMode(GL_PROJECTION);
//	Miscellaneous
	glLoadIdentity();
	gluOrtho2D(- GameConfig.WindowWidth / 2,
			GameConfig.WindowWidth / 2,
			- GameConfig.WindowHeight / 2,
			GameConfig.WindowHeight / 2);
	glMatrixMode(GL_MODELVIEW);
	return ;
}

bool graphicsEntry(int &argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(GameConfig.WindowWidth, GameConfig.WindowHeight);
//	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Exponential Chaos");
	if (GameConfig.WindowFullScreen)
		glutFullScreen();
//	Set movement functions below
	glutKeyboardFunc(kApiKeyboardFunc);
	glutKeyboardUpFunc(kApiKeyboardUpFunc);
	glutSpecialFunc(kApiSpecialFunc);
	glutSpecialUpFunc(kApiSpecialUpFunc);
	glutMouseFunc(graphicsMouseClick);
	glutMotionFunc(graphicsMouseMotionActive);
	glutPassiveMotionFunc(graphicsMouseMotionPassive);
	glutEntryFunc(graphicsMouseEntry);
	glutDisplayFunc(graphicsRender);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
//	All done, finished initialisation
	graphicsInit();
	eclogPost(1, "Done setting graphics properties");
	return true;
}
