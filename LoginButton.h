/* 
 * File:   LoginButton.h
 * Author: scribble
 *
 * Created on February 11, 2013, 8:15 AM
 */

#ifndef LOGINBUTTON_H
#define	LOGINBUTTON_H

#include "Button.h"

#define LOGIN_C 0
#define USER_NAME_C 1
#define PASSWORD_C 2

class LoginButton: public Button {
public:
    LoginButton();
    LoginButton(const LoginButton& orig);
    LoginButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color *fill_, Color *stroke_, Color *highlight_, Color *highlightStroke_);
    virtual ~LoginButton();
private:

};

#endif	/* LOGINBUTTON_H */
