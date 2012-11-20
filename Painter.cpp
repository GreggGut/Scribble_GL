/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

Painter::Painter() {
    
    scribbleArea = new ScribbleArea();
}

Painter::Painter(const Painter& orig) {
   
}

Painter::~Painter() {
    delete scribbleArea;
}

ScribbleArea* Painter::getScribbleArea(){
    return scribbleArea;
}


void Painter::Draw() {
    
     DrawPaths();
     DrawUI();

}

void Painter::DrawPaths(){
    
    glColor3f(scribbleArea->getPenColor().getRed(), scribbleArea->getPenColor().getGreen(), scribbleArea->getPenColor().getBlue());

    for ( int i = 0; i < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).size(); ++i )
    {

        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().size(); ++j )
        {

            glVertex3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getX(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getY(), 0.0f);
        }
        glEnd();
    }
   
    if (scribbleArea->getTempPath() == NULL)
        return;
    
    scribbleArea->setLockForPath(1);
   
    glBegin (GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j){
            
             glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(),scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
        }
    
    glEnd();    
   
    scribbleArea->setLockForPath(0);

}

void Painter::DrawUI(){

     switch (scribbleArea->getMode()){
        case WRITE:
           
            break;
            
        case ERASE:
            break;
            
        default:
            break;
    }
}