/* 
 * File:   MenuButton.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 5:56 AM
 */

#include "MenuButton.h"

MenuButton::MenuButton() {
}

MenuButton::MenuButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_,std::string image_, int id_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = image_;
    id = id_;
}

MenuButton::MenuButton(const MenuButton& orig) {
}

MenuButton::~MenuButton() {
}

std::string MenuButton::getImagePath(){
    return imagePath;
}

void MenuButton::setImagePath(std::string image){
    imagePath = image;
}

int MenuButton::getId(){
    return id;
}

void MenuButton::setSelectedImage(bool selected){
    
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