/* 
 * File:   Painter.cpp
 * Author: scribble
 * 
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

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

    DrawPaths();
    DrawMenu();

}

void Painter::DrawPaths() {

    glColor3f(scribbleArea->getPenColor().getRed(), scribbleArea->getPenColor().getGreen(), scribbleArea->getPenColor().getBlue());

    for (int i = 0; i < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).size(); ++i) {

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().size(); ++j) {

            glVertex3f(scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getX(), scribbleArea->getPathsOnPage().at(scribbleArea->getCurrentPage()).at(i)->getPath().at(j)->getY(), 0.0f);
        }
        glEnd();
    }

    if (scribbleArea->getTempPath() == NULL)
        return;

    scribbleArea->setLockForPath(1);

    glBegin(GL_LINE_STRIP);
    for (int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j) {

        glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(), scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
    }

    glEnd();

    scribbleArea->setLockForPath(0);

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