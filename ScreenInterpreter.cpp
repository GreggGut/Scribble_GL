/* 
 * File:   ScreenInterpreter.cpp
 * Author: scribble
 * 
 * Created on November 27, 2012, 2:40 PM
 */

#include "Painter.h"


#include "ScreenInterpreter.h"
#include "Menu.h"
#include "Login.h"

ScreenInterpreter::ScreenInterpreter() {

}

ScreenInterpreter::ScreenInterpreter(ScribbleArea *s, Menu *m, Login *l, FileList *fl, ColorPicker *cp, SizePicker *sp, Alert *a) {

    loginShown = 0;
    filelistShown = 0;
    alertShown = 0;
    colorpickerShown = 0;
    sizepickerShown = 0;
    loadingShown = 0;
    
    scribbleArea = s;
    menu = m;
    login = l;
    //keyboard = p->getKeyboard();
    alert = a;
    filelist = fl;
    colorPicker = cp;
    sizePicker = sp;

    menuState = 0;
    scribbleState = 0;
}

ScreenInterpreter::ScreenInterpreter(const ScreenInterpreter& orig) {
}

ScreenInterpreter::~ScreenInterpreter() {

}

//TO TEST: Make sure that drawing and pressing button works

void ScreenInterpreter::screenPressEvent(Point* point) {
    
    if (loadingShown == 1){
        point = NULL;
        delete point;
        return;
    }
    
    if (alertShown == 1) {
        alertPress(point);
    } else if (loginShown == 1) {
        loginPress(point);
    } else if (filelistShown == 1) {
        filelistPress(point);
    } else {

        if (colorpickerShown == 1 || sizepickerShown == 1) {
            if (colorpickerShown == 1) {
                colorPickerPress(point);
            } else {
                sizePickerPress(point);
            }
        } else {
            scribblePress(point);
        }
    }
}

void ScreenInterpreter::screenMoveEvent(Point* point) {
    
     if (loadingShown == 1){
        point = NULL;
        delete point;
        return;
    }
     
    if (alertShown == 1) {
        alertMove(point);
    } else if (loginShown == 1) {
        loginMove(point);
    } else if (filelistShown == 1) {
        filelistMove(point);
    } else {

        if (colorpickerShown == 1 || sizepickerShown == 1) {
            if (colorpickerShown == 1) {
                colorPickerMove(point);
            } else {
                sizePickerMove(point);
            }
        } else {
            scribbleMove(point);
        }
    }
}

void ScreenInterpreter::screenReleaseEvent() {
    
     if (loadingShown == 1){
        return;
    }
     
    if (alertShown == 1) {
        alertRelease();
    } else if (loginShown == 1) {
        loginRelease();
    } else if (filelistShown == 1) {
        filelistRelease();
    } else {
        if (colorpickerShown == 1 || sizepickerShown == 1) {
            if (colorpickerShown == 1) {
                colorPickerRelease();
            } else {
                sizePickerRelease();
            }
        }
        else {
            scribbleRelease();
        }
    }
}

ScribbleArea * ScreenInterpreter::getScribbleArea() {
    return scribbleArea;
}

void ScreenInterpreter::scribblePress(Point * point) {
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

    } else {
        //only scribble area
        scribbleState = 1;
        scribbleArea->screenPressEvent(point);
    }
}

void ScreenInterpreter::scribbleMove(Point * point) {
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

void ScreenInterpreter::loginPress(Point * point) {
    login->screenPressEvent(point);
}

void ScreenInterpreter::loginMove(Point * point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::loginRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::filelistPress(Point * point) {
    filelist->screenPressEvent(point);
}

void ScreenInterpreter::filelistMove(Point * point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::filelistRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::colorPickerPress(Point * point) {
    colorPicker->screenPressEvent(point);
}

void ScreenInterpreter::colorPickerMove(Point * point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::colorPickerRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::sizePickerPress(Point * point) {
    sizePicker->screenPressEvent(point);
}

void ScreenInterpreter::sizePickerMove(Point * point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::sizePickerRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::alertPress(Point * point) {
    alert->screenPressEvent(point);
}

void ScreenInterpreter::alertMove(Point * point) {
    //login->screenMoveEvent(point);
}

void ScreenInterpreter::alertRelease() {
    //login->screenReleaseEvent();
}

void ScreenInterpreter::showLoading(bool show) {
    loadingShown = show;
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

void ScreenInterpreter::showColorPicker(bool show) {
    colorpickerShown = show;
}

void ScreenInterpreter::showSizePicker(bool show) {
    sizepickerShown = show;
}

bool ScreenInterpreter::getShowSizePicker() {
    return sizepickerShown;
}

bool ScreenInterpreter::getShowLoading() {
    return loadingShown;
}

bool ScreenInterpreter::getShowColorPicker() {
    return colorpickerShown;
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

FileList * ScreenInterpreter::getFileList() {
    return filelist;
}

Menu * ScreenInterpreter::getMenu() {
    return menu;
}

Alert *ScreenInterpreter::getAlert() {
    return alert;
}

Login *ScreenInterpreter::getLogin(){
    return login;
}