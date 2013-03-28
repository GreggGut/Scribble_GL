/* 
 * File:   Login.h
 * Author: scribble
 *
 * Created on February 11, 2013, 3:58 AM
 */

#ifndef LOGIN_H
#define	LOGIN_H

#include <string>
#include "LoginButton.h"
#include <vector>
#include "defines.h"
//#include "ScreenInterpreter.h"

class ScreenInterpreter;

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
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    void callAction(int action);
    void setScreenInterpreter(ScreenInterpreter *s);
    std::string getUserName();
    std::string getPassword();
    std::string getTrueUserName();
    std::string getTruePassword();
    void setUserName(std::string user_);
    void setPassword(std::string pass_);
    bool getTypingUser();
    bool getTypingPassword();
    bool pointInsideArea(Point *point);
    void eraseUsername();
    void erasePassword();
    void setUserTyping();
    void setPasswordTyping();
    
private:
    int x;
    int y;
    int width;
    int height;
    std::string imagePath;
    std::vector<LoginButton *> *buttonArray;
    std::string username;
    std::string password;
    bool typingUser;
    bool typingPassword;
    ScreenInterpreter *screenInterpreter;
    void login();
};

#endif	/* LOGIN_H */

