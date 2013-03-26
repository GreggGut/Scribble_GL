/* 
 * File:   ColorPicker.h
 * Author: scribble
 *
 * Created on March 25, 2013, 4:42 AM
 */

#ifndef SIZEPICKER_H
#define	SIZEPICKER_H

#define BUTTON_1 41
#define BUTTON_2 42
#define BUTTON_3 43
#define BUTTON_5 44
#define BUTTON_7 45
#define BUTTON_10 46
#define BUTTON_13 47
#define BUTTON_15 48
#define BUTTON_20 49
#define BUTTON_30 50

#include "Picker.h"
#include <vector>
#include "PickerButton.h"

class SizePicker : public Picker {
public:
    SizePicker();
    SizePicker(const SizePicker& orig);
    SizePicker(int _x, int _y, int _width, int _height);
    virtual ~SizePicker();

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

#endif	/* SIZEPICKER_H */

