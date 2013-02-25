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
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'f':
            glutFullScreenToggle();
            break;
        case 'F':
            glutFullScreenToggle();
            break;
        case '1':
            painter->getLogin()->setUserName("user");
            painter->getLogin()->setPassword("Password");
            break;
        case '2':
            painter->getLogin()->setUserName("greg");
            painter->getLogin()->setPassword("pass");
            break;
        default:
            break;
    }

    glutPostRedisplay();
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
    glutPostRedisplay();
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

    if (painter->getInterpreter()->getScribbleArea()->getOwnershipValue() == 0) {
        painter->getInterpreter()->getScribbleArea()->getSender()->sendReleaseOwnership();
        while (painter->getInterpreter()->getScribbleArea()->getOwnershipValue() != 2);
    }

    delete sender;
    delete painter;
    //delete inputData;
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