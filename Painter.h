/* 
 * File:   Painter.h
 * Author: scribble
 *
 * Created on October 24, 2012, 10:15 AM
 */

#ifndef PAINTER_H
#define	PAINTER_H

#include <GL/glu.h>
#include "ScribbleArea.h"
#include "Menu.h"
#include "ScreenInterpreter.h"

class Painter {
   
public:
    Painter();
    Painter(const Painter& orig);
    virtual ~Painter();
    void Draw();
    ScribbleArea* getScribbleArea();
    Menu *getMenu();
    ScreenInterpreter *getInterpreter();
private:
    enum modes
    {
        WRITE, ERASE, MENU_PRESS, LOAD, SAVE_AS, COLOUR, SIZE_WRITE, SIZE_ERASE
    };
   
    ScreenInterpreter *interpreter;
    ScribbleArea *scribbleArea;
    Menu *menu;
    
    void DrawPaths();
    void DrawMenu();
};

#endif	/* PAINTER_H */

/* 
 * File:   Painter.h
 * Author: scribble
 *
 * Created on October 24, 2012, 10:15 AM
 */

#ifndef PAINTER_H
#define	PAINTER_H

#include <GL/glu.h>
#include "ScribbleArea.h"

class Painter {
   
public:
    Painter();
    Painter(const Painter& orig);
    virtual ~Painter();
    void Draw();
    ScribbleArea* getScribbleArea();
    
private:
    enum modes
    {
        WRITE, ERASE, MENU_PRESS, LOAD, SAVE_AS, COLOUR, SIZE_WRITE, SIZE_ERASE
    };
   
    ScribbleArea *scribbleArea;
    
    void DrawPaths();
    void DrawUI();
};

#endif	/* PAINTER_H */

