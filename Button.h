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

class Button {
public:
    Button();
    Button(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_);
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
    
protected:

    int x;
    int y;
    int width;
    int height;
    Color *fillColor;
    Color *strokeColor;
    Color *fill;
    Color *stroke;
    Color *highlight;
    Color *highlightStroke; 
    bool selected;
    int mode;
    int action;
};

#endif	/* BUTTON_H */

