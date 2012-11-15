/* 
 * File:   ScribbleArea.cpp
 * Author: scribble
 * 
 * Created on October 25, 2012, 2:17 PM
 */

#include "ScribbleArea.h"

ScribbleArea::ScribbleArea()
{

    penColor = Color();
    penSize = 1.0;
    currentPage = 0;

    /*   Point* point1 = new Point(0,0,0,100);
       Point* point2 = new Point(0,0,100,100);
    
       std::vector<Point *> mPointsVector;

       mPointsVector.push_back(point1);
  
       Path *path = new Path(mPointsVector.at(0), 0, penColor, penSize, 0, 1);

       path->addPoint(point2);
     */
    pathsOnPage.resize(5);
    Paths_IDs.resize(5);
    /*pathsOnPage.at(currentPage).push_back(path);*/

    mRequests = new Vector_Request();
    requestsMutex = new boost::mutex();

    //TODO server address and port should be variables that the user can change if needed
    std::string add = "127.0.0.1";
    mySender = new Sender(add, 21223);

    //TODO User will have to enter this (username and password)
    username = "greg";
    password = "pass";
    
    //Vector_Request* mRequests, boost::mutex * requestsMutex, std::string username);
    receiver = new Receiver(mRequests, requestsMutex, "greg");
    boost::thread(&ScribbleArea::NetworkRequestsAnalyzer, this);

    mySender->Login(username, password, receiver->GetMListeningPort());
    boost::thread(&ScribbleArea::SendTests, this);
}

ScribbleArea::ScribbleArea(const ScribbleArea& orig)
{
}

ScribbleArea::~ScribbleArea()
{

    delete mTempPath;
}

Color ScribbleArea::getPenColor()
{
    return penColor;
}

float ScribbleArea::getPenSize()
{
    return penSize;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void ScribbleArea::screenPressEvent(Point* point)
{
    //if point is NULL return, nothing to do
    if ( point == NULL )
    {
        return;
    }

    //If mode is write, initialize the writing sequence
    if ( this->mMode == WRITE )
    {
        //cleanRedoVector();
        lastPoint.setX(point->getX());
        lastPoint.setY(point->getY());
        scribbling = true;

        lockForTempPath.lock();
        mTempPath = new Path(point, this->mMode, this->penColor, this->penSize, Paths_IDs[currentPage]++);
        lockForTempPath.unlock();
    }

        //any other point needs to be delete
    else
    {
        delete point;
        point = NULL;
    }
}

/*! Screen Move Event
 *
 * \param *point A pointer to a Point object
 *
 * This function draws a line between a last point and the new point in Write mode or tries to delete a path on which the point passes through in Erase mode
 */
void ScribbleArea::screenMoveEvent(Point* point)
{
    if ( point == NULL )
    {
        return;
    }
    if ( scribbling == true )
    {
        pathsLock.lock();
        lockForTempPath.lock();
        mTempPath->addPoint(point);
        lockForTempPath.unlock();
        pathsLock.unlock();
    }
        //Here we can add more else if to enhance user experience by changing the color of the pressed button.
    else
    {
        delete point;
        point = NULL;
    }
}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void ScribbleArea::screenReleaseEvent(/*Points *point*/)
{
    if ( scribbling == true )
    {
        scribbling = false;

        pathsLock.lock();
        lockForTempPath.lock();

        if ( mTempPath->getPointsCount() < 3 )
        {
            delete mTempPath;
        }
        else
        {
            pathsOnPage.at(currentPage).push_back(mTempPath);
        }

        mTempPath = NULL;

        lockForTempPath.unlock();
        pathsLock.unlock();

    }

    else
    {

    }
}

/*! Set write mode
 *
 * This function set the mode to write, allowing the user to write on top of the PDF
 */
void ScribbleArea::write()
{
    mMode = WRITE;
    //modified = true;
}

void ScribbleArea::Draw()
{

    glColor3f(penColor.getRed(), penColor.getGreen(), penColor.getBlue());


    // glVertex3f(100,0,0);
    //glVertex3f(100,100,0);
    for ( int i = 0; i < pathsOnPage.at(currentPage).size(); ++i )
    {

        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < pathsOnPage.at(currentPage).at(i)->getPath().size(); ++j )
        {

            glVertex3f(pathsOnPage.at(currentPage).at(i)->getPath().at(j)->getX(), pathsOnPage.at(currentPage).at(i)->getPath().at(j)->getY(), 0.0f);
        }
        glEnd();
    }
    
    lockForTempPath.lock();
   
    glBegin (GL_LINE_STRIP);
        for (int j = 0; j < mTempPath->getPath().size(); ++j){
            
             glVertex3f(mTempPath->getPath().at(j)->getX(),mTempPath->getPath().at(j)->getY(), 0.0f);
        }
    
    glEnd();   
   
    lockForTempPath.unlock();

}

/**
 * This function check and executes all the requests that have been received from the server
 */
void ScribbleArea::NetworkRequestsAnalyzer()
{
    while ( checkMyRequests || mRequests->size() != 0 )
    {
        //sort the mRequests by requestID
        for ( uint i = 0; i < mRequests->size(); i++ )
        {

        }
        //if the first request in the queue has the nextRequestID then execute it
        //increase nextRequestID
        //repeat the 2 above steps until either all requests are met or the nextRequestID does not match the ID of the next request in the queue

        //Repeat the requests each 200 milliseconds
        boost::this_thread::sleep(boost::posix_time::milliseconds(200));

    }
}

void ScribbleArea::SendTests()
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    mySender->GetFilesList();
    //boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    mySender->RequestOwnership();

    Point m1(0, 0, 10, 10);
    Point m2(0, 0, 20, 20);
    Point m3(0, 0, 30, 30);
    Point m4(0, 0, 40, 40);

    std::vector<Point> mPoints;
    mPoints.push_back(m1);
    mPoints.push_back(m2);
    mPoints.push_back(m3);
    mPoints.push_back(m4);

    mySender->NewPath(3, true, 34567, true, 0);
    mySender->AddPoints(3, 4, mPoints);
    mySender->EndPath(3);
    mySender->Logout();

    std::cout << "Scribble area end of SendTests function" << std::endl;
}