/* 
 * File:   Menu.cpp
 * Author: scribble
 * 
 * Created on November 26, 2012, 6:11 PM
 */

#include "Menu.h"
#include "ScreenInterpreter.h"
#include "Sender.h"

#define BTN_WIDTH 40
#define BTN_HEIGHT 40

Menu::Menu() {
}

Menu::Menu(int x_, int y_, int w_, int h_) {

    std::string bgImage = "MenuBG.png";
    background = bgImage.insert(0,IMAGE_PATH);
    
    network = NETWORK;
    x = x_;
    y = y_;
    width = w_;
    height = h_;
    
    Color *white = new Color(WHITE);
    Color *green = new Color(GREEN);

    buttonArray = new std::vector<MenuButton *>;

    for (int i = 0; i < 9; ++i) {

        int type;
        int action;
        std::string fileName; 
        
        switch (i) {
            case 0:
                type = MOMENTARY;
                action = UNDO_C;
                fileName = "Undo.png";
                break;
            case 1:
                type = MOMENTARY;
                action = REDO_C;
                fileName = "Redo.png";
                break;
            case 2:
                type = MOMENTARY;
                action = CLEAR_ALL_C;
                fileName = "Clear.png";
                break;
            case 3:
                type = TOGGLE;
                action = WRITE_C;
                fileName = "Write.png";
                break;
            case 4:
                type = TOGGLE;
                action = ERASE_C;
                fileName = "Erase.png";
                break;
            case 5:
                type = PICKER;
                action = SIZE_C;
                fileName = "PenSize.png";
                break;
            case 6:
                type = PICKER;
                action = COLOUR_C;
                fileName = "PenColour.png";
                break;
            case 7:
                type = MOMENTARY;
                action = PREV_PG_C;
                fileName = "PreviousPage.png";
                break;
            case 8:
                type = MOMENTARY;
                action = NEXT_PG_C;
                fileName = "NextPage.png";
                break;
            default:
                type = MOMENTARY;
                action = NULL;
                fileName = "";
                break;
        }
        
        std::string imagePath; 
        if (fileName != "") {
            imagePath = fileName.insert(0,IMAGE_PATH);
        }
        
        else{
            imagePath = "";
        }
        
        MenuButton *btn = new MenuButton(5 + (BTN_WIDTH + 5) * i, 5, 40, 40, type, action,green,white,green,white,imagePath);
        buttonArray->push_back(btn);

    }

}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

std::vector <MenuButton *> * Menu::getButtonArray() {
    return buttonArray;
}

int Menu::getX() {
    return x;
}

int Menu::getY() {
    return y;
}

int Menu::getWidth() {
    return width;
}

int Menu::getHeight() {
    return height;
}

bool Menu::pointInsideArea(Point *point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
        return true;
    }

    return false;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void Menu::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

    for (int i = 0; i < buttonArray->size(); ++i) {

        if (buttonArray->at(i)->pointInsideArea(point) == 1) {

            switch (buttonArray->at(i)->getMode()) {
                case MOMENTARY:
                    callAction(buttonArray->at(i)->getAction());
                    break;
                case TOGGLE:
#warning //add toggling fucntionality
                    callAction(buttonArray->at(i)->getAction());
                    break;
                case PICKER:
                    break;
                default:
                    break;
            }

        }
    }

    delete point;
    point = NULL;
}

/*! Screen Move Event
 *
 * \param *point A pointer to a Point object
 *
 * This function draws a line between a last point and the new point in Write mode or tries to delete a path on which the point passes through in Erase mode
 */
void Menu::screenMoveEvent(Point* point) {
    /*if ( point == NULL )
    {
        return;
    }
    if ( scribbling == true )
    {
        pathsLock.lock();
        lockForTempPath.lock();
        mTempPath->addPoint(point);
        lockForTempPath.unlock();
        pathsLock.unlock();
    }
        //Here we can add more else if to enhance user experience by changing the color of the pressed button.
    else
    {
        delete point;
        point = NULL;
    }*/
}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void Menu::screenReleaseEvent(/*Points *point*/) {

}

void Menu::callAction(int action) {

    switch (action) {
        case UNDO_C:
            screenInterpreter->getScribbleArea()->undo();

            if (network == 1) {
                screenInterpreter->getScribbleArea()->getSender()->sendUndo(screenInterpreter->getScribbleArea()->getCurrentPage());
            }

            break;
        case REDO_C:
            screenInterpreter->getScribbleArea()->redo();
            if (network == 1) {
                screenInterpreter->getScribbleArea()->getSender()->sendRedo(screenInterpreter->getScribbleArea()->getCurrentPage());
            }
            break;
        case CLEAR_ALL_C:
            screenInterpreter->getScribbleArea()->clearAll();
            if (network == 1) {
                screenInterpreter->getScribbleArea()->getSender()->sendCleanAll(screenInterpreter->getScribbleArea()->getCurrentPage());
            }
            break;
        case ERASE_C:
            screenInterpreter->getScribbleArea()->setMode(ERASE);
            break;
        case WRITE_C:
            screenInterpreter->getScribbleArea()->setMode(WRITE);
            break;
        case PREV_PG_C:
            screenInterpreter->getScribbleArea()->previousPage();
            break;
        case NEXT_PG_C:
            screenInterpreter->getScribbleArea()->nextPage();
            break;
        default:
            break;
    }

}

void Menu::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}


 std::string Menu::getBackground(){
     return background;
 }
    