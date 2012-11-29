/* 
 * File:   ScreenInterpreter.h
 * Author: scribble
 *
 * Created on November 27, 2012, 2:40 PM
 */
 
#ifndef SCREENINTERPRETER_H
#define	SCREENINTERPRETER_H

#include "ScribbleArea.h"
#include "Menu.h"
#include "Point.h"

class ScreenInterpreter {
public:
    ScreenInterpreter();
    ScreenInterpreter(ScribbleArea *s, Menu *m);
    ScreenInterpreter(const ScreenInterpreter& orig);
    virtual ~ScreenInterpreter();
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    
private:
    ScribbleArea *scribbleArea;
    Menu *menu;
    int menuState;
    int scribbleState;
};

#endif	/* SCREENINTERPRETER_H */