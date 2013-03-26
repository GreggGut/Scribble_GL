/* 
 * File:   Alert.cpp
 * Author: scribble
 * 
 * Created on January 17, 2013, 4:38 PM
 */

#include "Alert.h"
#include "ScreenInterpreter.h"
#include "Sender.h"

Alert::Alert() {
}

 Alert::Alert(std::string title_, std::string message_,int type_){
     
     width = 486;
     height = 280;
     x = (WIDTH/2) - (width/2);
     y = (HEIGHT/2) - (height/2);
     
    std::string image = "AlertBG.png";
    imagePath = image.insert(0, IMAGE_PATH);
    
    buttonArray = new std::vector<AlertButton *>;
    
    for (int i = 0; i < 2; ++i) {

        int type = MOMENTARY;
        int action;
        int btnx;
        int btny;
        int btnw = 227;
        int btnh = 60;
        std::string buttonImage;

        switch (i) {
            case 0:
                action = OK_ALERT;
                buttonImage = "AlertOK.png";
                btnx = x+10;
                btny = y+210;
                break;
            case 1:
                action = CANCEL_ALERT;
                buttonImage = "AlertCancel.png";
                btnx = x+249;
                btny = y+210;
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

        AlertButton *btn = new AlertButton(btnx,btny,btnw,btnh,type,action,NULL,NULL,NULL,NULL,imagePath);
        buttonArray->push_back(btn);
    }
    
    setAlert(title_, message_, type_);
 }
  
 void Alert::setAlert(std::string title_, std::string message_, int type_){
     
     title = title_;
     message = message_;
     type = type_;
     
    
 }

Alert::Alert(const Alert& orig) {
}

Alert::~Alert() {
     for (uint i = 0; i < buttonArray->size(); i++) {
        delete buttonArray->at(i);
    }

    buttonArray->clear();

    delete buttonArray;
}

int Alert::getX() {
    return x;
}

int Alert::getY() {
    return y;
}

int Alert::getWidth() {
    return width;
}

int Alert::getHeight() {
    return height;
}

std::string Alert::getTitle() {
    return title;
}

std::string Alert::getMessage() {
    return message;
}

std::string Alert::getImagePath(){
    return imagePath;    
}

int Alert::getType() {
    return type;
}

std::vector <AlertButton *> * Alert::getButtonArray() {
    return buttonArray;
}

void Alert::setScreenInterpreter(ScreenInterpreter *s){
    screenInterpreter = s;
} 

bool Alert::pointInsideArea(Point *point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
        return true;
    }

    return false;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void Alert::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

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

    delete point;
    point = NULL;
}

/*! Screen Move Event
 *
 * \param *point A pointer to a Point object
 *
 * This function draws a line between a last point and the new point in Write mode or tries to delete a path on which the point passes through in Erase mode
 */
void Alert::screenMoveEvent(Point* point) {

}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void Alert::screenReleaseEvent(/*Points *point*/) {

}

void Alert::callAction(int action) {

    switch (action) {
        case OK_ALERT:
            
            if(type == CLEAR_ALL_ALERT){
                screenInterpreter->getScribbleArea()->clearAll(screenInterpreter->getScribbleArea()->getDocument()->getCurrentPage());
                if (NETWORK == 1) {
                    screenInterpreter->getScribbleArea()->getSender()->sendCleanAll(screenInterpreter->getScribbleArea()->getCurrentPage());
                }
                
                screenInterpreter->showAlert(0);
            }
            
            if (type == LOGIN_FAILED_ALERT){
                screenInterpreter->showAlert(0);
                
                screenInterpreter->getLogin()->callAction(LOGIN_C);
            }
            
            break;
            
        case CANCEL_ALERT:
         
                screenInterpreter->showAlert(0);
             
            break;
        default:
            break;
    }

}
