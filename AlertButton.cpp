/* 
 * File:   AlertButton.cpp
 * Author: scribble
 * 
 * Created on March 26, 2013, 2:17 AM
 */

#include "AlertButton.h"

AlertButton::AlertButton() {
}

AlertButton::AlertButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_,std::string image_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = image_;
}

AlertButton::AlertButton(const AlertButton& orig) {
}

AlertButton::~AlertButton() {
}

std::string AlertButton::getImagePath(){
    return imagePath;
}