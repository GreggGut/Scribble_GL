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

    //    boost::thread getInput(&InputData::run,inputData);

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);



    tcp::resolver::query query("localhost", "1234");
    tcp::resolver::iterator iterator = resolver.resolve(query);

    //NetworkClient
    NetworkClient client(io_service, iterator);

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    Sender s("greg");
    std::string toSend;
    //        toSend = s.Login("greg", "pass");
    //        c.write(sendMessage(toSend));

    toSend = s.GetFilesList();
    client.sendMessage(toSend);

    toSend = s.RequestOwnership();
    client.sendMessage(toSend);

    int pathID = 10;
    int page = 2;
    toSend = s.NewPath(pathID, true, 32453, true, page, 1);
    client.sendMessage(toSend);

    Point m1(0, 0, 10, 10);
    Point m2(0, 0, 20, 20);
    Point m3(0, 0, 30, 30);
    Point m4(0, 0, 40, 40);

    std::vector<Point> mPoints;
    mPoints.push_back(m1);
    mPoints.push_back(m2);
    mPoints.push_back(m3);
    mPoints.push_back(m4);
    toSend = s.AddPoints(mPoints);
    client.sendMessage(toSend);
    toSend = s.AddPoints(mPoints);
    client.sendMessage(toSend);
    toSend = s.EndPath();
    client.sendMessage(toSend);
    toSend = s.Undo(2);
    client.sendMessage(toSend);
    toSend = s.GetFilesList();
    client.sendMessage(toSend);
    toSend = s.DeletePath(page, pathID);
    client.sendMessage(toSend);
    toSend = s.ReleaseOwnership();
    client.sendMessage(toSend);

    glutMainLoop();

    client.close();
    t.join();

    return 0;
}