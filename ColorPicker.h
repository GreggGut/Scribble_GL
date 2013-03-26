/* 
 * File:   ColorPicker.h
 * Author: scribble
 *
 * Created on March 25, 2013, 4:42 AM
 */

#ifndef COLORPICKER_H
#define	COLORPICKER_H

#define BLACK_BUTTON 31
#define WHITE_BUTTON 32
#define GRAY_BUTTON 33
#define BLUE_BUTTON 34
#define GREEN_BUTTON 35
#define INDIGO_BUTTON 36
#define ORANGE_BUTTON 37
#define RED_BUTTON 38
#define VIOLET_BUTTON 39
#define YELLOW_BUTTON 40

#include "Picker.h"
#include "Color.h"
#include <vector>
#include "PickerButton.h"

class ColorPicker : public Picker {
public:
    ColorPicker();
    ColorPicker(const ColorPicker& orig);
    ColorPicker(int _x, int _y, int _width, int _height);
    virtual ~ColorPicker();

    std::vector<PickerButton *> *getButtonArray();
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    void callAction(int action);
    
     void setScreenInterpreter(ScreenInterpreter *s); 
private:

    std::vector<PickerButton *> *buttonArray;
       ScreenInterpreter *screenInterpreter;

};

#endif	/* COLORPICKER_H */

