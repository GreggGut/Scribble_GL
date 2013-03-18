/* 
 * File:   Keyboard.h
 * Author: scribble
 *
 * Created on February 11, 2013, 3:47 AM
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H
#include "Point.h"
//#include <KeyboardButton.h>
#include <vector>
#include "defines.h"
#include <string>

class ScreenInterpreter;

class Keyboard {
public:
    Keyboard();
    Keyboard(int x_, int y_, int w_, int h_);
    Keyboard(const Keyboard& orig);
    virtual ~Keyboard();
    bool pointInsideArea(Point *point);
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    //std::vector <KeyboardButton *> * getButtonArray();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void callAction(int action);
    void setScreenInterpreter(ScreenInterpreter *s);
    std::string getBackground();
 
private:
    bool network;
    int x;
    int y;
    int width;
    int height;
    //std::vector <KeyboardButton *> *buttonArray;
    ScreenInterpreter *screenInterpreter;
    std::string background;

};

#endif	/* KEYBOARD_H */

