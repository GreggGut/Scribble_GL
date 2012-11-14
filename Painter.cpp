/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

Painter::Painter() {
    ui = new UI();
    scribbleArea = new ScribbleArea();
}

Painter::Painter(const Painter& orig) {
   
}

Painter::~Painter() {
    delete ui;
    delete scribbleArea;
}

ScribbleArea* Painter::getScribbleArea(){
    return scribbleArea;
}


void Painter::Draw() {
    
    ui->Draw();
    scribbleArea->Draw();
}