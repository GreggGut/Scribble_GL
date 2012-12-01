/*
 * File:   Painter.cpp
 * Author: scribble
 *
 * Created on October 24, 2012, 10:15 AM
 */

#include "Painter.h"

Painter::Painter()
{

    menu = new Menu(0, 0, WIDTH, 50);
    scribbleArea = new ScribbleArea(0, 50, WIDTH, HEIGHT - 50);

    interpreter = new ScreenInterpreter(scribbleArea, menu);
}

Painter::Painter(const Painter& orig)
{

}

Painter::~Painter()
{
    delete scribbleArea;
    delete menu;
}

ScribbleArea* Painter::getScribbleArea()
{
    return scribbleArea;
}

Menu* Painter::getMenu()
{
    return menu;
}

ScreenInterpreter* Painter::getInterpreter()
{
    return interpreter;
}

void Painter::Draw()
{

    DrawPaths();
    DrawMenu();

}

void Painter::DrawPaths()
{

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

    scribbleArea->setLockForNetworkPath(1);
    if ( scribbleArea->getCurrentPage() == scribbleArea->getNetworkPage() && scribbleArea->getNetworkPath() != NULL )
    {
        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < scribbleArea->getNetworkPath()->getPath().size(); ++j )
        {

            glVertex3f(scribbleArea->getNetworkPath()->getPath().at(j)->getX(), scribbleArea->getNetworkPath()->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    scribbleArea->setLockForNetworkPath(0);

    if ( scribbleArea->getTempPath() == NULL )
        return;

    scribbleArea->setLockForPath(1);

    glBegin(GL_LINE_STRIP);
    for ( int j = 0; j < scribbleArea->getTempPath()->getPath().size(); ++j )
    {

        glVertex3f(scribbleArea->getTempPath()->getPath().at(j)->getX(), scribbleArea->getTempPath()->getPath().at(j)->getY(), 0.0f);
    }

    glEnd();

    scribbleArea->setLockForPath(0);

}

void Painter::DrawMenu()
{

    switch ( scribbleArea->getMode() )
    {
        case WRITE:

            break;

        case ERASE:
            break;

        default:
            break;
    }
}