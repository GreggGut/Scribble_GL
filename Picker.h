/* 
 * File:   Picker.h
 * Author: scribble
 *
 * Created on March 25, 2013, 4:42 AM
 */

#ifndef PICKER_H
#define	PICKER_H

#include "defines.h"
#include "Point.h"

class ScreenInterpreter;

class Picker {
public:
    Picker();
    Picker(int _x, int _y, int _width, int _height);
    Picker(const Picker& orig);
    virtual ~Picker();
   
    bool pointInsideArea(Point *point);
    std::string getImagePath();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

private:
    std::string imagePath;
    int x;
    int y;
    int width;
    int height;
 

};

#endif	/* PICKER_H */

