/* 
 * File:   ScreenInterpreter.cpp
 * Author: scribble
 * 
 * Created on November 27, 2012, 2:40 PM
 */

#include "ScreenInterpreter.h"
#include "Menu.h"
#include "Login.h"

ScreenInterpreter::ScreenInterpreter() {

}

ScreenInterpreter::ScreenInterpreter(ScribbleArea *s, Menu *m, Login *l) {

    loginShown = 0;
    filelistShown = 0;
    alertShown = 0;

    scribbleArea = s;
    menu = m;
    login = l;
    //keyboard = p->getKeyboard();
    //alert = p->getAlert();
    //filelist = p->getFileList();

    menuState = 0;
    scribbleState = 0;
}

ScreenInterpreter::ScreenInterpreter(const ScreenInterpreter& orig) {
}

ScreenInterpreter::~ScreenInterpreter() {

}

//TO TEST: Make sure that drawing and pressing button works

void ScreenInterpreter::screenPressEvent(Point* point) {

    if (alertShown == 1) {

    }
    else if (loginShown == 1) {
        loginPress(point);
    }
    else if (filelistShown == 1) {

    }
    else {
        scribblePress(point);
    }
}

void ScreenInterpreter::screenMoveEvent(Point* point) {
    if (alertShown == 1) {

    }
    else if (loginShown == 1) {
        loginMove(point);
    }
    else if (filelistShown == 1) {

    }
    else {
        scribbleMove(point);
    }
}

void ScreenInterpreter::screenReleaseEvent() {
    if (alertShown == 1) {

    }
    else if (loginShown == 1) {
        loginRelease();
    }
    else if (filelistShown == 1) {

    }
    else {
        scribbleRelease();
    }
}

ScribbleArea* ScreenInterpreter::getScribbleArea() {
    return scribbleArea;
}

void ScreenInterpreter::scribblePress(Point *point) {
    bool pointInMenu = menu->pointInsideArea(point);
    bool pointInScribble = scribbleArea->pointInsideArea(point);

    if (pointInMenu == true && pointInScribble == true) {
        //do screen event for both
        menuState = 1;
        scribbleState = 1;
        scribbleArea->screenPressEvent(point);
        menu->screenPressEvent(point);

    } else if (pointInMenu == true && pointInScribble == false) {
        //only menu action
        menuState = 1;
        menu->screenPressEvent(point);
        
#warning //can add hidding menu buttons here
        
    } else {
        //only scribble area
        scribbleState = 1;
        scribbleArea->screenPressEvent(point);
    }
}

void ScreenInterpreter::scribbleMove(Point *point) {
    bool pointInMenu = menu->pointInsideArea(point);
    bool pointInScribble = scribbleArea->pointInsideArea(point);

    if (pointInMenu == true && pointInScribble == true) {
        //do screen event for both
        scribbleState = 2;
        // menuState = 2;
        scribbleArea->screenMoveEvent(point);
        //menu->screenMoveEvent(point);
    } else if (pointInMenu == true && scribbleArea->getScribbling() == true) {
        //only menu action
        // menuState = 2;
        scribbleState = 0;
        scribbleArea->screenReleaseEvent();
        delete point;
        // menu->screenMoveEvent(point);
    } else {
        //only scribble area
        scribbleState = 2;
        scribbleArea->screenMoveEvent(point);
    }
}

void ScreenInterpreter::scribbleRelease() {
    if (scribbleState != 1) {
        scribbleState = 0;
        scribbleArea->screenReleaseEvent();
    }

    if (menuState == 1) {
        menuState = 0;
        //menu->screenReleaseEvent();
    }
}

void ScreenInterpreter::loginPress(Point *point) {
    login->screenPressEvent(point);
}

void ScreenInterpreter::loginMove(Point *point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::loginRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::showLogin(bool show) {
    loginShown = show;
}

void ScreenInterpreter::showFilelist(bool show) {
    filelistShown = show;
}

void ScreenInterpreter::showAlert(bool show) {
    alertShown = show;
}

bool ScreenInterpreter::getShowLogin() {
    return loginShown;
}

bool ScreenInterpreter::getShowFile() {
    return filelistShown;
}

bool ScreenInterpreter::getShowAlert() {
    return alertShown;
}