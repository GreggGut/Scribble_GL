/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

using namespace poppler;

Painter::Painter() {


    scribbleArea = new ScribbleArea(0, 50, WIDTH, HEIGHT - 50);
    menu = new Menu(0, 0, WIDTH, 50);
    menu->setScribbleArea(scribbleArea);

    interpreter = new ScreenInterpreter(scribbleArea, menu);
}

Painter::Painter(const Painter& orig) {

}

Painter::~Painter() {
    delete scribbleArea;
    delete menu;
}

ScribbleArea* Painter::getScribbleArea() {
    return scribbleArea;
}

Menu* Painter::getMenu() {
    return menu;
}

ScreenInterpreter* Painter::getInterpreter() {
    return interpreter;
}

void Painter::Draw() {

    //
    //glEnable(GL_BLEND);
    //
    //
    
    
    DrawPDF();
   
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    DrawPaths();
    
    
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
    
    DrawMenu();

    
    

}

void Painter::DrawPaths() {

    scribbleArea->setLockForPath(1);

    for (int i = 0; i < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).size(); ++i) {

        glColor3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getRed(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getGreen(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenColor().getBlue());
        glLineWidth(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPenWidth());
        
        /*glEnableClientState( GL_VERTEX_ARRAY );

        glVertexPointer(2,GL_INT,0,scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->pointsArray());
 
        glDrawArrays(GL_QUADS,0,2*scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPointsCount());
        */
        
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getX(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getY(), 0.0f);
        }
        glEnd();
    }

    scribbleArea->setLockForPath(0);

    scribbleArea->setLockForTempPath(1);
    if (scribbleArea->getTempPath() != NULL) {

        glColor3f(scribbleArea->getTempPath()->getPenColor().getRed(), scribbleArea->getTempPath()->getPenColor().getGreen(), scribbleArea->getTempPath()->getPenColor().getBlue());
        glLineWidth(scribbleArea->getTempPath()->getPenWidth());

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(), scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    scribbleArea->setLockForTempPath(0);
    //Path that is being received through the network
    scribbleArea->setLockForNetworkPath(1);

    if (scribbleArea->getCurrentPage() == scribbleArea->getNetworkPage() && scribbleArea->getNetworkPath() != NULL) {

        glColor3f(scribbleArea->getNetworkPath()->getPenColor().getRed(), scribbleArea->getNetworkPath()->getPenColor().getGreen(), scribbleArea->getNetworkPath()->getPenColor().getBlue());
        glLineWidth(scribbleArea->getNetworkPath()->getPenWidth());

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getNetworkPath()->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getNetworkPath()->getPath().at(j)->getX(), scribbleArea->getNetworkPath()->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    scribbleArea->setLockForNetworkPath(0);

}

void Painter::DrawMenu() {

    for (int i = 0; i < menu->getButtonArray()->size(); ++i) {

        glColor3f(menu->getButtonArray()->at(i)->getFillColor()->getRed(), menu->getButtonArray()->at(i)->getFillColor()->getGreen(), menu->getButtonArray()->at(i)->getFillColor()->getBlue());

        glBegin(GL_POLYGON);

        glVertex3i(menu->getButtonArray()->at(i)->getX(), menu->getButtonArray()->at(i)->getY(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX() + menu->getButtonArray()->at(i)->getWidth(), menu->getButtonArray()->at(i)->getY(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX() + menu->getButtonArray()->at(i)->getWidth(), menu->getButtonArray()->at(i)->getY() + menu->getButtonArray()->at(i)->getHeight(), 0);
        glVertex3i(menu->getButtonArray()->at(i)->getX(), menu->getButtonArray()->at(i)->getY() + menu->getButtonArray()->at(i)->getHeight(), 0);

        glEnd();

    }

}

void Painter::DrawPDF() {

#warning //add centering and scaling

    glRasterPos2i(scribbleArea->getDocument()->getX(), scribbleArea->getDocument()->getY());
    glPixelZoom(1.0, -1.0);

    glDrawPixels(scribbleArea->getDocument()->getImage()->width(), scribbleArea->getDocument()->getImage()->height(), GL_BGRA, GL_UNSIGNED_BYTE, scribbleArea->getDocument()->getImage()->data());
    // glScalef(1.2,1.2,0);
}