/* 
 * File:   main.h
 * Author: scribble
 *
 * Created on October 25, 2012, 1:17 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <GL/freeglut.h>
#include <GL/glu.h>

#include "Painter.h"
#include "InputData.h"
#include <boost/thread.hpp>

Painter *painter;
InputData *inputData;

void glInit (int argc, char** argv);

void resize(int width, int height);

void key(unsigned char key, int x, int y);

void idle(void);

void display(void);

int main(int argc, char *argv[]);

#endif	/* MAIN_H */
