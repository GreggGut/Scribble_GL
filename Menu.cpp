/* 
 * File:   Menu.cpp
 * Author: scribble
 * 
 * Created on November 26, 2012, 6:11 PM
 */

#include "Menu.h"

Menu::Menu() {
}

Menu::Menu(int x_, int y_, int w_, int h_) {
    x = x_;
    y = y_;
    width = w_;
    height = h_;
    
    buttonArray = new std::vector<Button *>;
    
    Button *chooseColor = new Button(10,10,50,50);
    
    buttonArray->push_back(chooseColor);
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

std::vector <Button *> * Menu::getButtonArray(){
    return buttonArray;
}

int Menu::getX() {
    return x;
}

int Menu::getY() {
    return y;
}

int Menu::getWidth() {
    return width;
}

int Menu::getHeight() {
    return height;
}
    
bool Menu::pointInsideArea(Point *point){
 
    //point has to be inside frame. could be changed but overlaps may occur
    if((point->getX() > x) && (point->getX() < width+x) && (point->getY() > y) && (point->getY() < height+y)){
        return true;
    }
    
    return false;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void Menu::screenPressEvent(Point* point)
{
    //if point is NULL return, nothing to do
    if ( point == NULL ){
        return;
    }
    
    for(int i = 0; i < buttonArray->size(); ++i){\
        
        if (buttonArray->at(i)->pointInsideArea(point) == 1){
            buttonArray->at(i)->setSelected();
            break;
        }
        
        else {
            continue;
        }
    }
    
    delete point;
    point = NULL;
}

/*! Screen Move Event
 *
 * \param *point A pointer to a Point object
 *
 * This function draws a line between a last point and the new point in Write mode or tries to delete a path on which the point passes through in Erase mode
 */
void Menu::screenMoveEvent(Point* point)
{
    /*if ( point == NULL )
    {
        return;
    }
    if ( scribbling == true )
    {
        pathsLock.lock();
        lockForTempPath.lock();
        mTempPath->addPoint(point);
        lockForTempPath.unlock();
        pathsLock.unlock();
    }
        //Here we can add more else if to enhance user experience by changing the color of the pressed button.
    else
    {
        delete point;
        point = NULL;
    }*/
}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void Menu::screenReleaseEvent(/*Points *point*/)
{
    for(int i = 0; i < buttonArray->size(); ++i){\
        
        if (buttonArray->at(i)->getSelected() == 1){
            buttonArray->at(i)->setSelected();
        }
        
        else {
            continue;
        }
    }
}