/* 
 * File:   Menu.h
 * Author: scribble
 *
 * Created on November 26, 2012, 6:11 PM
 */

#ifndef MENU_H
#define	MENU_H
#include "Point.h"
#include "MenuButton.h"
#include "Color.h"
#include <vector>
#include "defines.h"
#include <string>

class ScreenInterpreter;

class Menu {
public:
    Menu();
    Menu(int x_, int y_, int w_, int h_);
    Menu(const Menu& orig);
    virtual ~Menu();
    bool pointInsideArea(Point *point);
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    std::vector <MenuButton *> * getButtonArray();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void callAction(int action);
    void setScreenInterpreter(ScreenInterpreter *s);
    std::string getBackground();
    void handleOwnership();
    MenuButton *getOwnershipBTN();
    void getFilelist();
    
private:
    bool network;
    int x;
    int y;
    int width;
    int height;
    std::vector <MenuButton *> *buttonArray;
    ScreenInterpreter *screenInterpreter;
    std::string background;
    MenuButton *ownershipBTN;
};

#endif	/* MENU_H */

