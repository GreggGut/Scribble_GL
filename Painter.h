/* 
 * File:   Painter.h
 * Author: scribble
 *
 * Created on October 24, 2012, 10:15 AM
 */

#ifndef PAINTER_H
#define	PAINTER_H

#include <GL/glu.h>
#include <poppler/cpp/poppler-image.h>
#include "ScribbleArea.h"
#include "Menu.h"
#include "Login.h"
#include "Keyboard.h"
#include "ScreenInterpreter.h"
#include "Alert.h"
#include "FileList.h"
#include "lodepng.h"

class Painter {
   
public:
    Painter();
    Painter(const Painter& orig);
    virtual ~Painter();
    void Draw();
    ScribbleArea* getScribbleArea();
    Menu *getMenu();
    Login *getLogin();
    Keyboard *getKeyboard();
    Alert *getAlert();
    FileList *getFileList();
    ScreenInterpreter *getInterpreter();
    
    void showLogin(bool show);
    void showFilelist(bool show);
    void showAlert(bool show);
private:
   
    ScreenInterpreter *interpreter;
    ScribbleArea *scribbleArea;
    Menu *menu;
    Keyboard *keyboard;
    Login *login;
    Alert *alert;
    FileList *filelist;
    
    bool loginShown;
    bool filelistShown;
    bool alertShown;
    
    void drawPaths();
    void drawMenu();
    void drawPDF();
    void drawLogin();
    void drawKeyboard();
    void drawFileList();
    void drawAlert();
};

#endif	/* PAINTER_H */