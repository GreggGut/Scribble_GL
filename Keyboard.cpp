/* 
 * File:   Keyboard.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 3:47 AM
 */

#include "Keyboard.h"

Keyboard::Keyboard() {
}

Keyboard::Keyboard(int x_, int y_, int w_, int h_) {

    std::string bgImage = "MenuBG.png";
    background = bgImage.insert(0, IMAGE_PATH);

    network = NETWORK;
    x = x_;
    y = y_;
    width = w_;
    height = h_;

    //Color *white = new Color(WHITE);
    //Color *green = new Color(GREEN);

    buttonArray = new std::vector<KeyboardButton *>;

    for (int i = 0; i < 1; ++i) {

        int type;
        int action;
        int btnx;
        int btny;
        int btnw;
        int btnh;
        std::string buttonImage;

        switch (i) {
            case 0:
                type = MOMENTARY;
                action = Q;
                buttonImage = "Undo.png";
                btnx = 5 + (60 + 5) * i;
                btny = 5;
                btnw = 60;
                btnh = 60;
                break;
            default:
                type = MOMENTARY;
                action = NULL;
                buttonImage = "";
                break;
        }

        std::string imagePath;
        if (buttonImage != "") {
            imagePath = buttonImage.insert(0, IMAGE_PATH);
        } else {
            imagePath = "";
        }

        KeyboardButton *btn = new KeyboardButton(btnx, btny, btnw, btnh, type, action, NULL, NULL, NULL, NULL, imagePath, i);
        buttonArray->push_back(btn);

    }
}

Keyboard::Keyboard(const Keyboard& orig) {
}

Keyboard::~Keyboard() {

    for (uint i = 0; i < buttonArray->size(); i++) {
        delete buttonArray->at(i);
    }

    buttonArray->clear();

    delete buttonArray;

}

std::vector <KeyboardButton *> * Keyboard::getButtonArray() {
    return buttonArray;
}

int Keyboard::getX() {
    return x;
}

int Keyboard::getY() {
    return y;
}

int Keyboard::getWidth() {
    return width;
}

int Keyboard::getHeight() {
    return height;
}

bool Keyboard::pointInsideArea(Point *point) {

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
void Keyboard::screenPressEvent(Point* point) {
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
void Keyboard::screenMoveEvent(Point* point) {
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
void Keyboard::screenReleaseEvent(/*Points *point*/) {

}

void Keyboard::callAction(int action) {

    switch (action) {
        case Q:
          
            break;
    
        default:
            break;
    }

}

void Keyboard::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}

std::string Keyboard::getBackground() {
    return background;
}
