/*
 * File:   main.cpp
 * Author: scribble
 *
 * Created on October 24, 2012, 10:14 AM
 */

#include "main.h"
#include "Point.h"

void glInit(int argc, char** argv)
{

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
    glutIdleFunc(idle);
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, width, height, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void key(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 27:
            exit(0);
            break;
        case 'f':
            glutFullScreenToggle();
            break;
        case 'F':
            glutFullScreenToggle();
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        //std::cout << "down x: "<<x<< " y: "<< y <<"\n";

        if ( painter->getInterpreter()->getScribbleArea()->getScribbling() == true )
        {
            painter->getInterpreter()->screenMoveEvent(new Point(x, y));
        }

        else
        {
            painter->getInterpreter()->screenPressEvent(new Point(x, y));
        }
    }

    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        //std::cout << "up x: "<<x<< " y: "<< y <<"\n";
        painter->getInterpreter()->screenReleaseEvent();

    }
    glutPostRedisplay();
}

void idle()
{
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    painter->Draw();

    glutSwapBuffers();
    //glFlush();
}

int main(int argc, char *argv[])
{

    glInit(argc, argv);

    painter = new Painter();
    inputData = new InputData(painter->getInterpreter());

    boost::thread getInput(&InputData::run, inputData);

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);

    std::cout << "Connecting..." << std::endl;
    tcp::resolver::query query("localhost", "21223"); //"132.205.8.68"   localhost, MHO.encs.concordia.ca
    tcp::resolver::iterator iterator = resolver.resolve(query);

    //NetworkClient
    NetworkClient* client = new NetworkClient(io_service, iterator, painter->getScribbleArea());

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));


    //All the bellow is for testing
    Sender* sender = new Sender("greg", client);

    painter->getScribbleArea()->setSender(sender);

    //std::string toSend;
    sender->sendLogin("pass");
    //        c.write(sendMessage(toSend));

    sender->sendGetFilesList();
    sender->sendDownloadFile("0.pdf");
    sender->sendUpdateFileContent();

    sender->sendRequestOwnership();
    //
    //    int pathID = 10;
    //    int page = 0;
    //    sender->sendNewPath(pathID, true, 32453, page, 1);
    //
    //    Point* m1 = new Point(0, 0, 100, 100);
    //    Point* m2 = new Point(0, 0, 200, 200);
    //    Point* m3 = new Point(0, 0, 300, 300);
    //    Point* m4 = new Point(0, 0, 400, 600);
    //
    //    sender->sendPoints(m1);
    //    sender->sendPoints(m2);
    //    sender->sendPoints(m3);
    //    sender->sendPoints(m4);
    //
    //    pathID = 11;
    //
    //    sender->sendNewPath(pathID, true, 32453, page, 1);
    //
    //    m1 = new Point(0, 0, 10, 100);
    //    m2 = new Point(0, 0, 20, 200);
    //    m3 = new Point(0, 0, 30, 300);
    //    m4 = new Point(0, 0, 40, 600);
    //
    //    sender->sendPoints(m1);
    //    sender->sendPoints(m2);
    //    sender->sendPoints(m3);
    //    sender->sendPoints(m4);
    //
    //    pathID = 12;
    //
    //    sender->sendNewPath(pathID, true, 32453, page, 1);
    //
    //    m1 = new Point(0, 0, 10, 10);
    //    m2 = new Point(0, 0, 20, 20);
    //    m3 = new Point(0, 0, 30, 30);
    //    m4 = new Point(0, 0, 40, 60);
    //
    //    sender->sendPoints(m1);
    //    sender->sendPoints(m2);
    //    sender->sendPoints(m3);
    //    sender->sendPoints(m4);
    //
    //    pathID = 13;
    //
    //    sender->sendNewPath(pathID, true, 32453, page, 1);
    //
    //    m1 = new Point(0, 0, 10, 110);
    //    m2 = new Point(0, 0, 20, 120);
    //    m3 = new Point(0, 0, 30, 130);
    //    m4 = new Point(0, 0, 40, 160);
    //
    //    sender->sendPoints(m1);
    //    sender->sendPoints(m2);
    //    sender->sendPoints(m3);
    //    sender->sendPoints(m4);
    //
    //    pathID = 14;
    //
    //    sender->sendNewPath(pathID, true, 32453, page, 1);
    //
    //    m1 = new Point(0, 0, 110, 10);
    //    m2 = new Point(0, 0, 120, 20);
    //    m3 = new Point(0, 0, 130, 30);
    //    m4 = new Point(0, 0, 140, 60);
    //
    //    sender->sendPoints(m1);
    //    sender->sendPoints(m2);
    //    sender->sendPoints(m3);
    //    sender->sendPoints(m4);

    //sender->sendUndo(0);


    //s.sendAddPoints(mPoints);
    //sender->sendEndPath();
    //

    //    //s.sendUndo(2);
    //    //    sender->sendGetFilesList();
    //    //    sender->sendDeletePath(page, pathID);
    //    //    sender->sendReleaseOwnership();
    //    //Testing until here....
    //    std::cout << "Testing..." << std::endl;


    glutMainLoop();

    return 0;
}