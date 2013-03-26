/* 
 * File:   PickerButton.h
 * Author: scribble
 *
 * Created on March 25, 2013, 5:32 AM
 */

#ifndef PICKERBUTTON_H
#define	PICKERBUTTON_H

#include "Button.h"
#include <string>

class PickerButton: public Button {
public:
    PickerButton();
    PickerButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_, std::string image_);
    PickerButton(const PickerButton& orig);
    virtual ~PickerButton();
    
    std::string getImagePath();
    
private:
    
    std::string imagePath;

};

#endif	/* PICKERBUTTON_H */

