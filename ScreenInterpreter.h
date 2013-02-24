/* 
 * File:   ScreenInterpreter.h
 * Author: scribble
 *
 * Created on November 27, 2012, 2:40 PM
 */
 
#ifndef SCREENINTERPRETER_H
#define	SCREENINTERPRETER_H

#include "ScribbleArea.h"
//#include "Menu.h"
#include "Point.h"
//#include "Login.h"
#include "Keyboard.h"
#include "Alert.h"
#include "FileList.h"

class Menu;
class Login;

class ScreenInterpreter {
public:
    ScreenInterpreter();
    ScreenInterpreter(ScribbleArea *s, Menu *m, Login *l, FileList *fl);
    ScreenInterpreter(const ScreenInterpreter& orig);
    virtual ~ScreenInterpreter();
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    ScribbleArea* getScribbleArea();
    
    void showLogin(bool show);
    void showFilelist(bool show);
    void showAlert(bool show);
  
    bool getShowLogin();
    bool getShowFile();
    bool getShowAlert();
    
    FileList *getFileList();
    
private:
    ScribbleArea *scribbleArea;
    Menu *menu;
    Login *login;
    Keyboard *keyboard;
    Alert *alert;
    FileList *filelist;
    
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
    
    bool loginShown;
    bool filelistShown;
    bool alertShown;
};

#endif	/* SCREENINTERPRETER_H */