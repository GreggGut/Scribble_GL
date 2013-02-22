/* 
 * File:   FileListButton.cpp
 * Author: scribble
 * 
 * Created on February 21, 2013, 8:15 PM
 */

#include "FileListButton.h"

FileListButton::FileListButton() {
}

FileListButton::FileListButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color* fill_, Color* stroke_, Color* highlight_, Color* highlightStroke_, std::string image_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = image_;
}

FileListButton::FileListButton(const FileListButton& orig) {
}

FileListButton::~FileListButton() {
}

std::string FileListButton::getImagePath(){
    return imagePath;
}