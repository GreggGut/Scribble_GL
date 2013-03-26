/* 
 * File:   ColorPicker.cpp
 * Author: scribble
 * 
 * Created on March 25, 2013, 4:42 AM
 */

#include "SizePicker.h"
#include "ScreenInterpreter.h"
#include "Menu.h"

SizePicker::SizePicker() {
}

SizePicker::SizePicker(const SizePicker& orig) {
}

SizePicker::~SizePicker() {
    for (uint i = 0; i < buttonArray->size(); i++) {
        delete buttonArray->at(i);
    }

    buttonArray->clear();

    delete buttonArray;
}

SizePicker::SizePicker(int _x, int _y, int _width, int _height) : Picker(_x, _y, _width, _height) {

    buttonArray = new std::vector<PickerButton *>;

    for (int i = 0; i < 10; ++i) {

        int type;
        int action;
        int btnx;
        int btny;
        int btnw = 40;
        int btnh = 40;
        std::string buttonImage;

        switch (i) {
            case 0:
                type = MOMENTARY;
                action = BUTTON_1;
                buttonImage = "1px.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 1:
                type = MOMENTARY;
                action = BUTTON_2;
                buttonImage = "2px.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 2:
                type = MOMENTARY;
                action = BUTTON_3;
                buttonImage = "3px.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 3:
                type = MOMENTARY;
                action = BUTTON_5;
                buttonImage = "4px.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 4:
                type = MOMENTARY;
                action = BUTTON_7;
                buttonImage = "5px.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 5:
                type = MOMENTARY;
                action = BUTTON_10;
                buttonImage = "6px.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 6:
                type = MOMENTARY;
                action = BUTTON_13;
                buttonImage = "7px.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 7:
                type = MOMENTARY;
                action = BUTTON_15;
                buttonImage = "8px.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 8:
                type = MOMENTARY;
                action = BUTTON_20;
                buttonImage = "9px.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 9:
                type = MOMENTARY;
                action = BUTTON_30;
                buttonImage = "10px.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
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

        PickerButton *btn = new PickerButton(btnx, btny, btnw, btnh, type, action, NULL, NULL, NULL, NULL, imagePath);

        buttonArray->push_back(btn);

    }

}

void SizePicker::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}

std::vector<PickerButton *> *SizePicker::getButtonArray() {
    return buttonArray;
}

void SizePicker::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

    if (pointInsideArea(point) != 1) {
        //release picker
        screenInterpreter->showSizePicker(0);
    }
    else {
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
void SizePicker::screenMoveEvent(Point* point) {
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
void SizePicker::screenReleaseEvent(/*Points *point*/) {

}

void SizePicker::callAction(int action) {

    std::string _image;

    switch (action) {
        case BUTTON_1:

            _image = "1px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(1);

            break;
        case BUTTON_2:

            _image = "2px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(2);

            break;

        case BUTTON_3:

            _image = "3px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(3);

            break;

        case BUTTON_5:

            _image = "4px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(4);

            break;

        case BUTTON_7:

            _image = "5px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(5);

            break;

        case BUTTON_10:

            _image = "6px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(6);

            break;

        case BUTTON_13:

            _image = "7px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(7);

            break;

        case BUTTON_15:

            _image = "8px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(8);

            break;

        case BUTTON_20:

            _image = "9px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(9);

            break;

        case BUTTON_30:

            _image = "10px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenWidth(10);

            break;

        default:

            _image = "2px.png";
            screenInterpreter->getMenu()->getButtonArray()->at(5)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(2);

            break;
    }

}