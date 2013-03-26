/* 
 * File:   ColorPicker.cpp
 * Author: scribble
 * 
 * Created on March 25, 2013, 4:42 AM
 */

#include "ColorPicker.h"
#include "ScreenInterpreter.h"
#include "Menu.h"

ColorPicker::ColorPicker() {
}

ColorPicker::ColorPicker(const ColorPicker& orig) {
}

ColorPicker::~ColorPicker() {
    for (uint i = 0; i < buttonArray->size(); i++) {
        delete buttonArray->at(i);
    }

    buttonArray->clear();

    delete buttonArray;
}

ColorPicker::ColorPicker(int _x, int _y, int _width, int _height) : Picker(_x, _y, _width, _height) {

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
                action = BLACK_BUTTON;
                buttonImage = "BlackButton.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 1:
                type = MOMENTARY;
                action = WHITE_BUTTON;
                buttonImage = "WhiteButton.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 2:
                type = MOMENTARY;
                action = GRAY_BUTTON;
                buttonImage = "GrayButton.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 3:
                type = MOMENTARY;
                action = BLUE_BUTTON;
                buttonImage = "BlueButton.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 4:
                type = MOMENTARY;
                action = GREEN_BUTTON;
                buttonImage = "GreenButton.png";
                btnx = _x + (9 + (btnw + 8) * i);
                btny = _y + 21;
                break;
            case 5:
                type = MOMENTARY;
                action = INDIGO_BUTTON;
                buttonImage = "IndigoButton.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 6:
                type = MOMENTARY;
                action = ORANGE_BUTTON;
                buttonImage = "OrangeButton.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 7:
                type = MOMENTARY;
                action = RED_BUTTON;
                buttonImage = "RedButton.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 8:
                type = MOMENTARY;
                action = VIOLET_BUTTON;
                buttonImage = "VioletButton.png";
                btnx = _x + (9 + (btnw + 8) * (i - 5));
                btny = _y + 70;
                break;
            case 9:
                type = MOMENTARY;
                action = YELLOW_BUTTON;
                buttonImage = "YellowButton.png";
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

void ColorPicker::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}

std::vector<PickerButton *> *ColorPicker::getButtonArray() {
    return buttonArray;
}

void ColorPicker::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

    if (pointInsideArea(point) != 1) {
        //release picker
        screenInterpreter->showColorPicker(0);
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
void ColorPicker::screenMoveEvent(Point* point) {
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
void ColorPicker::screenReleaseEvent(/*Points *point*/) {

}

void ColorPicker::callAction(int action) {

    std::string _image;

    switch (action) {
        case BLACK_BUTTON:

            _image = "Color_Black.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_BLACK));

            break;
        case WHITE_BUTTON:

            _image = "Color_White.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_WHITE));

            break;

        case GRAY_BUTTON:

            _image = "Color_Gray.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_GRAY));

            break;

        case BLUE_BUTTON:

            _image = "Color_Blue.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_BLUE));

            break;

        case GREEN_BUTTON:

            _image = "Color_Green.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_GREEN));

            break;

        case INDIGO_BUTTON:

            _image = "Color_Indigo.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_INDIGO));

            break;

        case ORANGE_BUTTON:

            _image = "Color_Orange.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_ORANGE));

            break;

        case RED_BUTTON:

            _image = "Color_Red.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_RED));

            break;

        case VIOLET_BUTTON:

            _image = "Color_Violet.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_VIOLET));

            break;

        case YELLOW_BUTTON:

            _image = "Color_Yellow.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_YELLOW));

            break;

        default:

            _image = "Color_Black.png";
            screenInterpreter->getMenu()->getButtonArray()->at(6)->setImagePath(_image.insert(0, IMAGE_PATH));
            screenInterpreter->getScribbleArea()->setPenColor(Color(PALETTE_BLACK));

            break;
    }

}