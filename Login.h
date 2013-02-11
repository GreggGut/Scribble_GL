/* 
 * File:   Login.h
 * Author: scribble
 *
 * Created on February 11, 2013, 3:58 AM
 */

#ifndef LOGIN_H
#define	LOGIN_H

#include <string>

class Login {
public:
    Login();
    Login(int x_, int y_, int w_, int h_);
    Login(const Login& orig);
    virtual ~Login();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    std::string getImagePath();

private:
    int x;
    int y;
    int width;
    int height;
    std::string imagePath;
};

#endif	/* LOGIN_H */

