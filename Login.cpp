/* 
 * File:   Login.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 3:58 AM
 */

#include "Login.h"
#include "ScreenInterpreter.h"
#include "Sender.h"

Login::Login() {
}

Login::Login(int x_, int y_, int w_, int h_) {
    x = x_;
    y = y_;
    width = w_;
    height = h_;

    std::string fileName = "Login.png";
    imagePath = fileName.insert(0, IMAGE_PATH);

    typingPassword = 0;
    typingUser = 0;

    username = "";
    password = "";

    buttonArray = new std::vector<LoginButton *>;

    for (int i = 0; i < 3; ++i) {

        int type;
        int action;
        int btnx;
        int btny;
        int btnw;
        int btnh;

        switch (i) {
            case 0:
                type = MOMENTARY;
                action = LOGIN_C;
                btnx = 374;
                btny = 273;
                btnw = 221;
                btnh = 60;
                break;
            case 1:
                type = MOMENTARY;
                action = USER_NAME_C;
                btnx = 60;
                btny = 113;
                btnw = 534;
                btnh = 60;
                break;
            case 2:
                type = MOMENTARY;
                action = PASSWORD_C;
                btnx = 60;
                btny = 193;
                btnw = 534;
                btnh = 60;
                break;
            default:
                type = MOMENTARY;
                action = NULL;
                btnx = 0;
                btny = 0;
                btnw = 0;
                btnh = 0;
                break;
        }


        LoginButton *btn = new LoginButton(btnx + x, btny + y, btnw, btnh, type, action, NULL, NULL, NULL, NULL);
        buttonArray->push_back(btn);

    }
}

Login::Login(const Login& orig) {
}

Login::~Login() {
}

int Login::getX() {
    return x;
}

int Login::getY() {
    return y;
}

int Login::getWidth() {
    return width;
}

int Login::getHeight() {
    return height;
}

std::string Login::getImagePath() {
    return imagePath;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void Login::screenPressEvent(Point* point) {
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
void Login::screenMoveEvent(Point* point) {

}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void Login::screenReleaseEvent(/*Points *point*/) {

}

void Login::callAction(int action) {

    switch (action) {
        case LOGIN_C:

            if (username == "" || password == "") {
                std::cout << "ERROR: no username or password\n";
                screenInterpreter->getAlert()->setAlert("Login Failed", "Do you want to retry?", LOGIN_FAILED_ALERT);
                screenInterpreter->showAlert(1);
            } else {
                login();
            }

            break;
        case USER_NAME_C:
            typingUser = 1;
            typingPassword = 0;

            break;
        case PASSWORD_C:
            typingUser = 0;
            typingPassword = 1;
            break;

        default:
            break;
    }

}

void Login::login() {

    typingPassword = 0;
    typingUser = 0;
    
    screenInterpreter->showLoading(1);

    if (screenInterpreter->getScribbleArea()->getSender()->connectToServer()) {

        screenInterpreter->getScribbleArea()->getSender()->sendLogin(username, password);

        while (screenInterpreter->getScribbleArea()->getNetworkActivity() == ScribbleArea::NetworkActivity::WAITING_LOGIN);


        if (screenInterpreter->getScribbleArea()->getNetworkActivity() == ScribbleArea::NetworkActivity::LOGIN_FAILED) {

            screenInterpreter->getAlert()->setAlert("Login Failed", "Do you want to retry?", LOGIN_FAILED_ALERT);
            screenInterpreter->showLoading(0);
            screenInterpreter->showAlert(1);
            return;
        }

        screenInterpreter->getScribbleArea()->getSender()->sendGetFilesList();
        while (screenInterpreter->getScribbleArea()->getNetworkActivity() == ScribbleArea::NetworkActivity::WAITING_FOR_FILE_LIST);

        if (screenInterpreter->getScribbleArea()->getFilesOnServer().size() > 0) {
            screenInterpreter->showLogin(0);
            screenInterpreter->getFileList()->setFileList(screenInterpreter->getScribbleArea()->getFilesOnServer());
              screenInterpreter->showLoading(0);
            screenInterpreter->showFilelist(1);
        } else {
            std::cout << "ERROR: No files on server\n";
        }
    } else {
        screenInterpreter->getAlert()->setAlert("Login Failed", "Do you want to retry?", LOGIN_FAILED_ALERT);
        screenInterpreter->showLoading(0);
        screenInterpreter->showAlert(1);
        return;
    }
}

void Login::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}

std::string Login::getUserName() {

    if (username == "")
        return "Username";
    
    return username;
}

std::string Login::getPassword() {

    if (password == "")
        return "Password";
    
    std::string hidden = password;
    hidden.replace(0,hidden.size(),hidden.size(),'*');
    
    return hidden;
}

std::string Login::getTrueUserName() {

    return username;
}

std::string Login::getTruePassword() {

    return password;
}

void Login::setUserName(std::string user_) {
    username = user_;
}

void Login::setPassword(std::string pass_) {
    password = pass_;
}

bool Login::getTypingUser() {
    return typingUser;
}

bool Login::getTypingPassword() {
    return typingPassword;
}

bool Login::pointInsideArea(Point *point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
        return true;
    }

    return false;
}

void Login::erasePassword() {
    int length = password.length();

    if (length > 0) {
        password.resize(length - 1);
    }
}

void Login::eraseUsername() {
    int length = username.length();

    if (length > 0) {
        username.resize(length - 1);
    }
}

void Login::setUserTyping() {
    typingUser = 1;
    typingPassword = 0;
}

void Login::setPasswordTyping() {
    typingUser = 0;
    typingPassword = 1;
}