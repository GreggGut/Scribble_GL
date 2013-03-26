/* 
 * File:   Picker.cpp
 * Author: scribble
 * 
 * Created on March 25, 2013, 4:42 AM
 */

#include "Picker.h"
#include "PickerButton.cpp"

Picker::Picker() {
}

Picker::Picker(const Picker& orig) {
}

Picker::~Picker() {
}

Picker::Picker(int _x, int _y, int _width, int _height){
    
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    std::string _imagePath = "PickerBG.png";
    imagePath = _imagePath.insert(0,IMAGE_PATH);
    
}

std::string Picker::getImagePath() {
    return imagePath;
}

int Picker::getX() {
    return x;
}

int Picker::getY() {
    return y;
}

int Picker::getWidth() {
    return width;
}

int Picker::getHeight() {
    return height;
}

bool Picker::pointInsideArea(Point *point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
        return true;
    }

    return false;
}

