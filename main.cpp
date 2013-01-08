/*
 * File:   main.cpp
 * Author: scribble
 *
 * Created on October 24, 2012, 10:14 AM
 */

#include "main.h"

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
    switch (key)
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
}

RequestMessage encodeMessage(std::string line)
{
    //We need to add an end of line to the message
    line += '\n';
    RequestMessage msg;
    msg.body_length(std::strlen(line.c_str()));
    std::memcpy(msg.body(), line.c_str(), msg.body_length());
    msg.encode_header();

    return msg;

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
    //        s.Login("greg", "pass");
    //        c.write(sendMessage(toSend));

    sender->sendGetFilesList();
    sender->sendUpdateFileContent();

    sender->sendRequestOwnership();

//    int pathID = 10;
//    int page = 0;
//    sender->sendNewPath(pathID, true, 32453, true, page, 1);
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
//    //s.sendAddPoints(mPoints);
//    sender->sendEndPath();
//
    sender->sendDownloadFile("hello");
//    //s.sendUndo(2);
//    //    sender->sendGetFilesList();
//    //    sender->sendDeletePath(page, pathID);
//    //    sender->sendReleaseOwnership();
//    //Testing until here....
//    std::cout << "Testing..." << std::endl;
    glutMainLoop();

    client->close();
    t.join();

    //We need to find a way to stop the dataInput thread...
    //and then getInput.join();
    //getInput.join();
    delete sender;
    delete client;

    return 0;
}