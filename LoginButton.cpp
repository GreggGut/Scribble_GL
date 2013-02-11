/* 
 * File:   LoginButton.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 8:15 AM
 */

#include "LoginButton.h"

LoginButton::LoginButton() {
}

LoginButton::LoginButton(const LoginButton& orig) {
}

LoginButton::LoginButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color* fill_, Color* stroke_, Color* highlight_, Color* highlightStroke_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    
}

LoginButton::~LoginButton() {
}

