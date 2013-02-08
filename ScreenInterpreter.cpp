/* 
 * File:   ScreenInterpreter.cpp
 * Author: scribble
 * 
 * Created on November 27, 2012, 2:40 PM
 */

#include "ScreenInterpreter.h"

ScreenInterpreter::ScreenInterpreter() {

}

ScreenInterpreter::ScreenInterpreter(ScribbleArea *s, Menu *m) {
    scribbleArea = s;
    menu = m;
    menuState = 0;
    scribbleState = 0;
}

ScreenInterpreter::ScreenInterpreter(const ScreenInterpreter& orig) {
}

ScreenInterpreter::~ScreenInterpreter() {

}

//TO TEST: Make sure that drawing and pressing button works

void ScreenInterpreter::screenPressEvent(Point* point) {
    //state 1
    //std::cout << "press event\n";
    bool pointInMenu = menu->pointInsideArea(point);
    bool pointInScribble = scribbleArea->pointInsideArea(point);

    if (pointInMenu == true && pointInScribble == true) {
        //do screen event for both
        menuState = 1;
        scribbleState = 1;
        scribbleArea->screenPressEvent(point);
        menu->screenPressEvent(point);

    }
    else if (pointInMenu == true && pointInScribble == false) {
        //only menu action
        menuState = 1;
        menu->screenPressEvent(point);
    }
    else {
        //only scribble area
        scribbleState = 1;
        scribbleArea->screenPressEvent(point);
    }
}

void ScreenInterpreter::screenMoveEvent(Point* point) {
    //state 2
    //std::cout << "move event\n";
    bool pointInMenu = menu->pointInsideArea(point);
    bool pointInScribble = scribbleArea->pointInsideArea(point);

    if (pointInMenu == true && pointInScribble == true) {
        //do screen event for both
        scribbleState = 2;
        // menuState = 2;
        scribbleArea->screenMoveEvent(point);
        //menu->screenMoveEvent(point);
    }
    else if (pointInMenu == true && scribbleArea->getScribbling() == true) {
        //only menu action
        // menuState = 2;
         scribbleState = 0;
          scribbleArea->screenReleaseEvent();
          delete point;
        // menu->screenMoveEvent(point);
    }
    else {
        //only scribble area
        scribbleState = 2;
        scribbleArea->screenMoveEvent(point);
    }
}

void ScreenInterpreter::screenReleaseEvent() {
    //state 0

    //std::cout << "end event\n";
    if (scribbleState != 1) {
        scribbleState = 0;
        scribbleArea->screenReleaseEvent();
    }

    if (menuState == 1) {
        menuState = 0;
        //menu->screenReleaseEvent();
    }
}

ScribbleArea* ScreenInterpreter::getScribbleArea() {
    return scribbleArea;
}