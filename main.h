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

#include <boost/bind.hpp>
#include <boost/asio.hpp>
//#include "NetworkConnection.h"

#include <cstdlib>
#include "RequestMessage.h"
#include "Sender.h"
#include "NetworkClient.h"
#include <sstream>

Painter *painter;
InputData *inputData;
Sender* sender;
boost::thread getInput;

void glInit (int argc, char** argv);

void resize(int width, int height);

void key(unsigned char key, int x, int y);

void specialKey(int key, int x, int y);

void mouse(int button, int state, int x, int y);

void idle(void);

void display(void);

void close(void);

int main(int argc, char *argv[]);

void mouseCoords(int x, int y);
#endif	/* MAIN_H */
