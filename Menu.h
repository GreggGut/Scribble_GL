/* 
 * File:   Menu.h
 * Author: scribble
 *
 * Created on November 26, 2012, 6:11 PM
 */

#ifndef MENU_H
#define	MENU_H
#include "Point.h"

class Menu {
public:
    Menu();
    Menu(int x, int y, int w, int h);
    Menu(const Menu& orig);
    virtual ~Menu();
    bool pointInsideArea(Point *point);
private:
    int xPos;
    int yPos;
    int width;
    int height;
};

#endif	/* MENU_H */

