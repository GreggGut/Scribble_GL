/*
 * File:   main.cpp
 * Author: scribble
 *
 * Created on October 24, 2012, 10:14 AM
 */

#include "main.h"
#include "Point.h"
#include "Login.h"

void glInit(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Scribble");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseCoords);
    glutIdleFunc(idle);
    glutSpecialFunc(specialKey);
    glutCloseFunc(close);
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, width, height, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void key(unsigned char key, int x, int y) {

    if (key == '\t') {
        if (painter->getInterpreter()->getLogin()->getTypingUser() == 1) {
            painter->getInterpreter()->getLogin()->setPasswordTyping();
        }
        else if (painter->getInterpreter()->getLogin()->getTypingPassword() == 1) {
            painter->getInterpreter()->getLogin()->setUserTyping();
        }
    }
    else if (key == '\r') {
        painter->getInterpreter()->getLogin()->callAction(LOGIN_C);
    }
    else if (key == '\b') {
        if (painter->getInterpreter()->getLogin()->getTypingUser() == 1) {
            
            if (painter->getInterpreter()->getLogin()->getTrueUserName().size() > 0){
                std::string str = painter->getInterpreter()->getLogin()->getTrueUserName();
                str.resize(str.length() - 1);
                
                painter->getInterpreter()->getLogin()->setUserName(str);
            }
        }
        else if (painter->getInterpreter()->getLogin()->getTypingPassword() == 1) {
           if (painter->getInterpreter()->getLogin()->getTruePassword().size() > 0){
                std::string str = painter->getInterpreter()->getLogin()->getTruePassword();
                str.resize(str.length() - 1);
                
                painter->getInterpreter()->getLogin()->setPassword(str);
            }
        }
    }
    else {
        if (painter->getInterpreter()->getLogin()->getTypingPassword() == 1) {
            stringstream ss;
            ss << painter->getInterpreter()->getLogin()->getTruePassword() << key;
            painter->getInterpreter()->getLogin()->setPassword(ss.str());
        }

        if (painter->getInterpreter()->getLogin()->getTypingUser() == 1) {
            stringstream ss;
            ss << painter->getInterpreter()->getLogin()->getTrueUserName() << key;
            painter->getInterpreter()->getLogin()->setUserName(ss.str());
        }
    }

}

void specialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            painter->getLogin()->setUserName("user");
            painter->getLogin()->setPassword("Password");
            break;
        case GLUT_KEY_F2:
            painter->getLogin()->setUserName("greg");
            painter->getLogin()->setPassword("pass");
            break;
        case GLUT_KEY_F3:
            painter->getLogin()->setUserName("scribble");
            painter->getLogin()->setPassword("app1234");
            break;
        case GLUT_KEY_F10:
            glutFullScreenToggle();
            break;
        case GLUT_KEY_F12:
            exit(0);
            break;
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //std::cout << "down x: "<<x<< " y: "<< y <<"\n";

        if (painter->getInterpreter()->getScribbleArea()->getScribbling() == false) {
            painter->getInterpreter()->screenPressEvent(new Point(x, y));

        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        //std::cout << "up x: "<<x<< " y: "<< y <<"\n";
        painter->getInterpreter()->screenReleaseEvent();

    }

}

void mouseCoords(int x, int y) {

    if (painter->getInterpreter()->getScribbleArea()->getScribbling() == true) {
        painter->getInterpreter()->screenMoveEvent(new Point(x, y));
    }
}

void idle() {
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    painter->Draw();

    glutSwapBuffers();
    glFlush();
}

void close() {
    delete sender;
    delete painter;
}

int main(int argc, char *argv[]) {

    glInit(argc, argv);

    painter = new Painter();
    inputData = new InputData(painter->getInterpreter());

    getInput = boost::thread(&InputData::run, inputData);

    sender = new Sender(painter->getScribbleArea());

    painter->getInterpreter()->showLogin(1);

    glutMainLoop();

    return 0;
}