/* 
 * File:   Login.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 3:58 AM
 */

#include "Login.h"

Login::Login() {
}

Login::Login(int x_, int y_, int w_, int h_){
    x = x_;
    y = y_;
    width = w_;
    height = h_;
    imagePath = "./resources/images/Login.png";
}

Login::Login(const Login& orig) {
}

Login::~Login() {
}

int Login::getX() {
    return x;
}

int Login::getY() {
    return y;
}

int Login::getWidth() {
    return width;
}

int Login::getHeight() {
    return height;
}

std::string Login::getImagePath() {
    return imagePath;
}

