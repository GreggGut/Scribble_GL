/* 
 * File:   Alert.h
 * Author: scribble
 *
 * Created on January 17, 2013, 4:38 PM
 */

#ifndef ALERT_H
#define	ALERT_H

#define CLEAR_ALL_ALERT 10
#define LOGIN_FAILED_ALERT 11
#define FILE_LIST_FAILED_ALERT 12

#include <string>
#include "AlertButton.h"
#include <vector>

class ScreenInterpreter;

class Alert {
public:
    Alert();
    Alert(std::string title_, std::string message_, int type_);
    Alert(const Alert& orig);
    virtual ~Alert();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    std::string getTitle();
    std::string getMessage();
    int getType();
    bool pointInsideArea(Point *point);
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    void setScreenInterpreter(ScreenInterpreter *s);
    void callAction(int action);
    std::vector <AlertButton *> * getButtonArray();
    std::string getImagePath();
    void setAlert(std::string title_, std::string message_, int type_);
    
private:
    int x;
    int y;
    int width;
    int height;
    std::string title;
    std::string message;
    int type;
    std::string imagePath;

    std::vector <AlertButton *> *buttonArray;
    ScreenInterpreter *screenInterpreter;

};

#endif	/* ALERT_H */

