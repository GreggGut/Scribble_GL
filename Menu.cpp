/* 
 * File:   Menu.cpp
 * Author: scribble
 * 
 * Created on November 26, 2012, 6:11 PM
 */

#include "Menu.h"
#include "ScribbleArea.h"

Menu::Menu() {
}

Menu::Menu(int x_, int y_, int w_, int h_) {
    x = x_;
    y = y_;
    width = w_;
    height = h_;

    buttonArray = new std::vector<Button *>;

    Button *btn1 = new Button(5, 5, 40, 40, MOMENTARY, UNDO_C);
    Button *btn2 = new Button(50, 5, 40, 40, MOMENTARY, REDO_C);

    buttonArray->push_back(btn1);
    buttonArray->push_back(btn2);
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

std::vector <Button *> * Menu::getButtonArray() {
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

bool Menu::pointInsideArea(Point *point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
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
void Menu::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

#warning 
    //problems here since clicking anywhere else will cause error

    for (int i = 0; i < buttonArray->size(); ++i) {

        if (buttonArray->at(i)->pointInsideArea(point) == 1) {

            switch (buttonArray->at(i)->getMode()) {
                case MOMENTARY:
                    callAction(buttonArray->at(i)->getAction());
                    break;
                case TOGGLE:
                    break;
                case PICKER:
                    break;
                default:
                    break;
            }
            
        }
        else {
            switch (buttonArray->at(i)->getMode()) {
                case MOMENTARY:
                    break;
                case TOGGLE:
                    break;
                case PICKER:
                    break;
                default:
                    break;
            }

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
void Menu::screenMoveEvent(Point* point) {
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
void Menu::screenReleaseEvent(/*Points *point*/) {

}

void Menu::callAction(int action){
    
    switch (action){
        case UNDO_C:
            scribbleArea->undo();
            break;
        case REDO_C:
            scribbleArea->redo();
            break;
        default:
            break;
    }
    
}

void Menu::setScribbleArea(ScribbleArea *s){
        scribbleArea = s;   
}