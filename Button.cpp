/* 
 * File:   Button.cpp
 * Author: scribble
 * 
 * Created on November 29, 2012, 9:17 AM
 */

#include "Button.h"

Button::Button() {
}

Button::Button(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_){
    
    x = x_;
    y = y_;
    width = w_;
    height = h_;
    mode = mode_;
    action = action_;
    selected = 0;
    fillColor = fill_;
    strokeColor = stroke_;
    fill = fill_;
    stroke = stroke_;
    highlight = highlight_;
    highlightStroke = highlightStroke_;
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
    
Color* Button::getFillColor(){
    return fillColor;
}

Color* Button::getStrokeColor(){
    return strokeColor;
}

void Button::setSelected(){
    
    if (selected == 1){
        selected = 0;
        fillColor = fill;
        strokeColor = stroke;
    }
    
    else {
        selected = 1;
        fillColor = highlight;
        strokeColor = highlightStroke;
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

int Button::getMode(){
    return mode;
}

int Button::getAction(){
    
    return action;
}