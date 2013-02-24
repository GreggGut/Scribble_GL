/* 
 * File:   FileListCell.cpp
 * Author: scribble
 * 
 * Created on February 23, 2013, 8:25 PM
 */

#include "FileListCell.h"

FileListCell::FileListCell() {
}

FileListCell::FileListCell(int x_, int y_, int w_, int h_, int mode_, int action_, Color* fill_, Color* stroke_, Color* highlight_, Color* highlightStroke_, std::string fileName_, uint id_):Button(x_,y_,w_,h_,mode_,action_,fill_,stroke_,highlight_,highlightStroke_){
    imagePath = "FileListCell.png";
    imagePath.insert(0,IMAGE_PATH);
    fileName = fileName_;
    id = id_;
}

FileListCell::FileListCell(const FileListCell& orig) {
}

FileListCell::~FileListCell() {
}

std::string FileListCell::getImagePath(){
    return imagePath;
}

std::string FileListCell::getFileName(){
    return fileName;
}

uint FileListCell::getID(){
    return id;
}