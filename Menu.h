/* 
 * File:   Menu.h
 * Author: scribble
 *
 * Created on November 26, 2012, 6:11 PM
 */

#ifndef MENU_H
#define	MENU_H
#include "Point.h"
#include "Button.h"
#include <vector>

class Menu {
public:
    Menu();
    Menu(int x_, int y_, int w_, int h_);
    Menu(const Menu& orig);
    virtual ~Menu();
    bool pointInsideArea(Point *point);
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    std::vector <Button *> * getButtonArray();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
   
private:
    int x;
    int y;
    int width;
    int height;
    std::vector <Button *> *buttonArray;
};

#endif	/* MENU_H */

