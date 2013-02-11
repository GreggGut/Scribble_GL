/* 
 * File:   MenuButton.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 5:56 AM
 */

#include "MenuButton.h"

MenuButton::MenuButton() {
}

MenuButton::MenuButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_){
    Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_);
}

MenuButton::MenuButton(const MenuButton& orig) {
}

MenuButton::~MenuButton() {
}

