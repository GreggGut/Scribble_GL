/* 
 * File:   main.cpp
 * Author: scribble
 *
 * Created on October 24, 2012, 10:14 AM
 */

#include "main.h"
#include "Point.h"

void glInit (int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Scribble");
    
    glClearColor(1.0,1.0,1.0,1.0);
    
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
    
    gluOrtho2D(0.0,width,height,0.0); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
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

void mouse(int button, int state, int x, int y){
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
         painter->getInterpreter()->screenPressEvent(new Point(0,0,x,y));
         std::cout << "down\n";
    }
    
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        painter->getInterpreter()->screenReleaseEvent();
        std::cout << "up\n";
    }
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

int main(int argc, char *argv[])
{
  
    glInit(argc, argv);
    
    painter = new Painter();
    inputData = new InputData(painter->getInterpreter());

//    boost::thread getInput(&InputData::run,inputData);
    
    glutMainLoop();
   
    return 0;
}