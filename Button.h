/* 
 * File:   Button.h
 * Author: scribble
 *
 * Created on November 29, 2012, 9:17 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H
#include "Color.h"
#include "Point.h"

#define MOMENTARY 0
#define TOGGLE 1
#define PICKER 2

#define UNDO_C 0
#define REDO_C 1
#define ERASE_C 2
#define SIZE_C 3
#define COLOUR_C 4
#define NEXT_PAGE_C 5
#define PREVIOUS_PAGE_C 6
#define CLEAR_ALL_C 7

class Button {
public:
    Button();
    Button(int x_, int y_, int w_, int h_, int mode_, int action_);
    Button(const Button& orig);
    virtual ~Button();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    Color *getFillColor();
    Color *getStrokeColor();
    void setSelected();
    bool getSelected();
    bool pointInsideArea(Point *point);
    int getMode();
    int getAction();
    
private:

    int x;
    int y;
    int width;
    int height;
    Color *fillColor;
    Color *strokeColor;
    bool selected;
    int mode;
    int action;
};

#endif	/* BUTTON_H */

