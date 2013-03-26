/* 
 * File:   AlertButton.h
 * Author: scribble
 *
 * Created on March 26, 2013, 2:17 AM
 */

#ifndef ALERTBUTTON_H
#define	ALERTBUTTON_H

#define OK_ALERT 0
#define CANCEL_ALERT 1

#include "Button.h"
#include <string>

class AlertButton: public Button {
public:
    AlertButton();
    AlertButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_, std::string image_);
    AlertButton(const AlertButton& orig);
    virtual ~AlertButton();
    
    std::string getImagePath();
    
private:
    
    std::string imagePath;

};

#endif	/* ALERTBUTTON_H */

