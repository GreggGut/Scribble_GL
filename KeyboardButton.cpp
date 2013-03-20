/* 
 * File:   KeyboardButton.cpp
 * Author: scribble
 * 
 * Created on March 18, 2013, 2:44 AM
 */

#include "KeyboardButton.h"

KeyboardButton::KeyboardButton() {
}

KeyboardButton::KeyboardButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_,std::string image_, int id_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = image_;
    id = id_;
}

KeyboardButton::KeyboardButton(const KeyboardButton& orig) {
}

KeyboardButton::~KeyboardButton() {
}

std::string KeyboardButton::getImagePath(){
    return imagePath;
}

void KeyboardButton::setImagePath(std::string image){
    imagePath = image;
}

int KeyboardButton::getId(){
    return id;
}

void KeyboardButton::setSelectedImage(bool selected){
    
    if (selected == 1){

        if (imagePath.find(".png") != std::string::npos){
            imagePath.replace(imagePath.end()-4, imagePath.end(), "_Selected.png");
            setEnabled(1);
        } 
        
        else {
           //not an image
        }
    }
    
    else {
        
        if (imagePath.find("_Selected.png") != std::string::npos){
            imagePath.replace(imagePath.end()-13, imagePath.end(), ".png");
            setEnabled(0);
        }
        
        else {
            //not an image
        }
    }
}