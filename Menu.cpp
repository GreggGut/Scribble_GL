/* 
 * File:   Menu.cpp
 * Author: scribble
 * 
 * Created on November 26, 2012, 6:11 PM
 */

#include "Menu.h"

Menu::Menu() {
}

Menu::Menu(int x, int y, int w, int h) {
    xPos = x;
    yPos = y;
    width = w;
    height = h;
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

bool Menu::pointInsideArea(Point *point){
 
    //point has to be inside frame. could be changed but overlaps may occur
    if((point->getX() > xPos) && (point->getX() < width+xPos) && (point->getY() > yPos) && (point->getY() < height+yPos)){
        return true;
    }
    
    return false;
}
