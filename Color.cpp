/* 
 * File:   Color.cpp
 * Author: scribble
 * 
 * Created on November 5, 2012, 6:01 PM
 */

#include "Color.h"
#include "Alert.h"

Color::Color() {
    //black by default
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

Color::Color(int color) {

    switch (color) {

        case GREEN:
            red = convertToFloat(102);
            green = convertToFloat(204);
            blue = convertToFloat(102);
            break;
        case LIGHT_GRAY:
            red = convertToFloat(220);
            green = convertToFloat(220);
            blue = convertToFloat(220);
            break;
        case DARK_GRAY:
            red = convertToFloat(130);
            green = convertToFloat(130);
            blue = convertToFloat(130);
            break;
        case WHITE:
            red = convertToFloat(255);
            green = convertToFloat(255);
            blue = convertToFloat(255);
            break;
        case PALETTE_BLACK:
            red = convertToFloat(0);
            green = convertToFloat(0);
            blue = convertToFloat(0);
            break;
        case PALETTE_WHITE:
            red = convertToFloat(255);
            green = convertToFloat(255);
            blue = convertToFloat(255);
            break;
        case PALETTE_GRAY:
            red = convertToFloat(128);
            green = convertToFloat(128);
            blue = convertToFloat(128);
            break;
        case PALETTE_BLUE:
            red = convertToFloat(0);
            green = convertToFloat(0);
            blue = convertToFloat(153);
            break;
        case PALETTE_GREEN:
            red = convertToFloat(0);
            green = convertToFloat(102);
            blue = convertToFloat(0);
            break;
        case PALETTE_INDIGO:
            red = convertToFloat(0);
            green = convertToFloat(102);
            blue = convertToFloat(102);
            break;
        case PALETTE_ORANGE:
            red = convertToFloat(255);
            green = convertToFloat(102);
            blue = convertToFloat(0);
            break;
        case PALETTE_RED:
            red = convertToFloat(204);
            green = convertToFloat(0);
            blue = convertToFloat(0);
            break;
        case PALETTE_VIOLET:
            red = convertToFloat(153);
            green = convertToFloat(0);
            blue = convertToFloat(204);
            break;
        case PALETTE_YELLOW:
            red = convertToFloat(255);
            green = convertToFloat(204);
            blue = convertToFloat(0);
            break;
        default:
            red = convertToFloat(0);
            green = convertToFloat(0);
            blue = convertToFloat(0);
            break;
    }
}
//values from 0-255

Color::Color(float r, float g, float b) {
    red = convertToFloat(r);
    green = convertToFloat(g);
    blue = convertToFloat(b);
}

Color::Color(const Color& orig) {
    red = orig.red;
    green = orig.green;
    blue = orig.blue;
}

Color::~Color() {
}

float Color::getRed() {
    return red;
}

float Color::getGreen() {
    return green;
}

float Color::getBlue() {
    return blue;
}

void Color::setColor(int r, int g, int b) {
    red = convertToFloat(r);
    green = convertToFloat(g);
    blue = convertToFloat(b);
}

/*void Color::setColorFromColor(float r, float g, float b){
#warning //error
    red = r;
    //green = g;
    //blue = b;
}*/

float Color::convertToFloat(int x) {

    return x / 255.0;
}