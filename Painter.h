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
#include "ColorPicker.h"
#include "SizePicker.h"
#include "lodepng.h"
#include <FTGL/ftgl.h>
#include "Color.h"

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
    ColorPicker *getColorPicker();
    SizePicker *getSizePicker();
    ScreenInterpreter *getInterpreter();
    
private:
   
    ScreenInterpreter *interpreter;
    ScribbleArea *scribbleArea;
    Menu *menu;
    Keyboard *keyboard;
    Login *login;
    Alert *alert;
    FileList *filelist;
    ColorPicker *colorPicker;
    SizePicker *sizePicker;
    
    void drawPaths();
    void drawMenu();
    void drawPDF();
    void drawLogin();
    void drawKeyboard();
    void drawFileList();
    void drawAlert();
    void drawColorPicker();
    void drawSizePicker();
    
    void getPNG(std::string imagePath, int _x, int _y);
    void drawText(std::string text, int size, int x, int y, Color color);
    void drawPixels(int _x, int _y, int width, int height, std::vector<unsigned char> _image);
};

#endif	/* PAINTER_H */