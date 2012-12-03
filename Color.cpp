/* 
 * File:   Color.cpp
 * Author: scribble
 * 
 * Created on November 5, 2012, 6:01 PM
 */

#include "Color.h"

Color::Color() {
    //black by default
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

//values from 0-255
Color::Color(float r, float g, float b) {
    red = r/255.0;
    green = g/255.0;
    blue = b/255.0;
}


Color::Color(const Color& orig) {
    red = orig.red;
    green = orig.green;
    blue = orig.blue;
}

Color::~Color() {
}

float Color::getRed(){
     return red;
 }
 
float Color::getGreen(){
     return green;
 }

float Color::getBlue(){
     return blue;
 }

void Color::setColor(int r, int g, int b){
    red = r/255.0;
    green = g/255.0;
    blue = b/255.0;
}