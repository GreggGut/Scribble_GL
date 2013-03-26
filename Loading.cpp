/* 
 * File:   Loading.cpp
 * Author: scribble
 * 
 * Created on March 26, 2013, 6:47 AM
 */

#include "Loading.h"

Loading::Loading() {

    topAngle = 0;
    bottomAngle = 720;


    std::string bgImage = "LoadingBG.png";
    background = bgImage.insert(0, IMAGE_PATH);

    std::string topImage = "LoadingTop.png";
    topRing = topImage.insert(0, IMAGE_PATH);

    std::string bottomImage = "LoadingBottom.png";
    bottomRing = bottomImage.insert(0, IMAGE_PATH);
}

Loading::Loading(const Loading& orig) {
}

Loading::~Loading() {
}

std::string Loading::getTopRing() {
    return topRing;
}

std::string Loading::getBottomRing() {
    return bottomRing;
}

std::string Loading::getBackground() {
    return background;
}

int Loading::getTopAngle() {
    return topAngle;
}

int Loading::getBottomAngle() {
    return bottomAngle;
}

void Loading::setTopAngle() {

    if (topAngle == 720) {
        topAngle = 0;
    }
    else {
        topAngle = topAngle + 45;
    }
}

void Loading::setBottomAngle() {
    if (bottomAngle == 0) {
        bottomAngle = 720;
    }
    else {
        bottomAngle = bottomAngle - 45;
    }
}

void Loading::reset(){
 
    bottomAngle = 720;
    topAngle = 0;
}