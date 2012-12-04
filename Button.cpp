/* 
 * File:   Button.cpp
 * Author: scribble
 * 
 * Created on November 29, 2012, 9:17 AM
 */

#include "Button.h"

Button::Button() {
}

Button::Button(int x_, int y_, int w_, int h_){
    
    x = x_;
    y = y_;
    width = w_;
    height = h_;
   
    selected = 0;
    fillColor = new Color(100,20,20);
    strokeColor = new Color(100,30,30);
}

Button::Button(const Button& orig) {
}

Button::~Button() {
}

int Button::getX() {
    return x;
}

int Button::getY() {
    return y;
}

int Button::getWidth() {
    return width;
}

int Button::getHeight() {
    return height;
}
    
Color * Button::getFillColor(){
    return fillColor;
}

Color * Button::getStrokeColor(){
    return strokeColor;
}

void Button::setSelected(){
    
    if (selected == 1){
        selected = 0;
        fillColor->setColor(100,20,20);
        strokeColor->setColor(100,30,30);
    }
    
    else {
        selected = 1;
        fillColor->setColor(20,20,100);
        strokeColor->setColor(30,30,100);
    }
}

bool Button::getSelected(){
    return selected;
}

bool Button::pointInsideArea(Point *point){
 
    //point has to be inside frame. could be changed but overlaps may occur
    if((point->getX() > x) && (point->getX() < width+x) && (point->getY() > y) && (point->getY() < height+y)){
        return true;
    }
    
    return false;
}