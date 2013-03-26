/* 
 * File:   PickerButton.cpp
 * Author: scribble
 * 
 * Created on March 25, 2013, 5:32 AM
 */

#include "PickerButton.h"

PickerButton::PickerButton() {
}

PickerButton::PickerButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_,std::string image_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = image_;
}

PickerButton::PickerButton(const PickerButton& orig) {
}

PickerButton::~PickerButton() {
}

std::string PickerButton::getImagePath(){
    return imagePath;
}