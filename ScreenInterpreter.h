/* 
 * File:   ScreenInterpreter.h
 * Author: scribble
 *
 * Created on November 27, 2012, 2:40 PM
 */
 
#ifndef SCREENINTERPRETER_H
#define	SCREENINTERPRETER_H

#include "ScribbleArea.h"
#include "Point.h"
#include "Keyboard.h"
#include "Alert.h"
#include "FileList.h"
#include "Menu.h"
#include "ColorPicker.h"
#include "SizePicker.h"

class Menu;
class Login;

class ScreenInterpreter {
public:
    ScreenInterpreter();
    ScreenInterpreter(ScribbleArea *s, Menu *m, Login *l, FileList *fl,ColorPicker *cp, SizePicker *sp, Alert *a);
    ScreenInterpreter(const ScreenInterpreter& orig);
    virtual ~ScreenInterpreter();
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    ScribbleArea* getScribbleArea();
    
    void showLogin(bool show);
    void showFilelist(bool show);
    void showAlert(bool show);
    void showColorPicker(bool show);
    void showSizePicker(bool show);
    void showLoading(bool show);
    
    bool getShowLogin();
    bool getShowFile();
    bool getShowAlert();
    bool getShowColorPicker();
    bool getShowSizePicker();
    bool getShowLoading();
    
    FileList *getFileList();
    Menu *getMenu();
    Alert *getAlert();
    Login *getLogin();
    
private:
    ScribbleArea *scribbleArea;
    Menu *menu;
    Login *login;
    Keyboard *keyboard;
    Alert *alert;
    FileList *filelist;
    ColorPicker *colorPicker;
    SizePicker *sizePicker;
    
    int menuState;
    int scribbleState;
    
    void scribblePress(Point *point);
    void scribbleMove(Point *point);
    void scribbleRelease();
    
    void loginPress(Point *point);
    void loginMove(Point *point);
    void loginRelease();
   
    void filelistPress(Point *point);
    void filelistMove(Point *point);
    void filelistRelease();
    
    void colorPickerPress(Point *point);
    void colorPickerMove(Point *point);
    void colorPickerRelease();
    
    void sizePickerPress(Point *point);
    void sizePickerMove(Point *point);
    void sizePickerRelease();
    
    void alertPress(Point *point);
    void alertMove(Point *point);
    void alertRelease();
    
    bool loginShown;
    bool filelistShown;
    bool alertShown;
    bool colorpickerShown;
    bool sizepickerShown;
    bool loadingShown;
};

#endif	/* SCREENINTERPRETER_H */