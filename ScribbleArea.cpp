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

    pathsOnPage.resize(5);
    Paths_IDs.resize(5);

    //Used to keep track of all the pending received requests (from the Scribble Server)
    mRequests = new Vector_Request();

    //Used to lock the request vector (mRequests) when accessing it
    requestsMutex = new boost::mutex();

    //TODO server address and port should be variables that the user can change if needed
    std::string add = "127.0.0.1";
    serverListeningPort = 21223;
    mySender = new Sender(add, serverListeningPort);

    //TODO User will have to enter this (username and password)
    username = "greg13";
    password = "pass";

    //Vector_Request* mRequests, boost::mutex * requestsMutex, std::string username);
    checkMyRequests = true;
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
    delete myNetworkPath;

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
   
    if (mTempPath == NULL)
        return;
    
    lockForTempPath.lock();
   
    glBegin (GL_LINE_STRIP);
        for (int j = 0; j < mTempPath->getPath().size(); ++j){
            
             glVertex3f(mTempPath->getPath().at(j)->getX(),mTempPath->getPath().at(j)->getY(), 0.0f);
        }
    
    glEnd();    
   
    lockForTempPath.unlock();

    if ( mTempPath != NULL )
    {
        lockForTempPath.lock();

        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < mTempPath->getPath().size(); ++j )
        {

            glVertex3f(mTempPath->getPath().at(j)->getX(), mTempPath->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();

        lockForTempPath.unlock();
    }

    if ( myNetworkPath != NULL && myNetworkPathPage == currentPage )
    {
        //TODO We need a lock here
        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < myNetworkPath->getPath().size(); ++j )
        {

            glVertex3f(myNetworkPath->getPath().at(j)->getX(), myNetworkPath->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }


}

bool compareByRequestID(Request *a, Request *b)
{
    return a->getRequestID() < b->getRequestID();
}

bool isNull(Request *a)
{
    return a == NULL;
}

/**
 * This function check and executes all the requests that have been received from the server
 */
void ScribbleArea::NetworkRequestsAnalyzer()
{
    while ( checkMyRequests || mRequests->size() != 0 )
    {
        //Removing all NULL from the vector and then sorting the vector by nextRequestID
        mRequests->erase(std::remove_if(mRequests->begin(), mRequests->end(), isNull), mRequests->end());
        //sort the mRequests by requestID
        std::sort(mRequests->begin(), mRequests->end(), compareByRequestID);

        std::cout << "Requests in queue: " << mRequests->size() << std::endl;
        for ( uint i = 0; i < mRequests->size(); i++ )
        {
            std::cout << "ID: " << mRequests->at(i)->getRequestID() << "  type:  " << mRequests->at(i)->getRequestType() << std::endl;
        }

        std::cout<<"nextRequestID: "<<nextRequestID<<std::endl;

        for ( uint i = 0; i < mRequests->size(); i++ )
        {
            if ( mRequests->at(i)->getRequestID() == nextRequestID )
            {
                //Determine request type and act upon it
                switch ( mRequests->at(i)->getRequestType() )
                {
                    case Request::ADDPOINTS:
                    {
                        std::cout << " ADDPOINTS" << std::endl;
                        //AddPoints - username - requestID++ - pathID - numberOfPoints - Points (vector of points*)


                        int nPoints = ( ( AddPointsToPathRequest* ) mRequests->at(i) )->getNumberOfPoints();
                        //TOCONF pathID with the new points seems useless
                        int pathID = ( ( AddPointsToPathRequest* ) mRequests->at(i) )->getPathID();
                        std::vector<Point *> myNewNetworkPoints = ( ( AddPointsToPathRequest * ) mRequests->at(i) )->getPoints();

                        for ( int i = 0; i < nPoints; i++ )
                        {
                            myNetworkPath->addPoint(myNewNetworkPoints[i]);
                        }

                        break;
                    }
                    case Request::NEWPATH:
                    {
                        std::cout << " NEWPATH" << std::endl;

                        Color color = ( ( NewPathRequest* ) mRequests->at(i) )->getColor();
                        int page = ( ( NewPathRequest* ) mRequests->at(i) )->getPage();
                        int pathID = ( ( NewPathRequest* ) mRequests->at(i) )->getPathID();
                        int width = ( ( NewPathRequest* ) mRequests->at(i) )->getWidth();
                        bool active = ( ( NewPathRequest* ) mRequests->at(i) )->isActive();
                        bool mode = ( ( NewPathRequest* ) mRequests->at(i) )->isMode();

                        //new Path
                        //(Point* point, int mode, Color color, int width, int id, bool fin, bool active

                        //This constructor does not have an initial point so we have to be careful when drawing this.. we might get a NULL pointer
                        Path * path = new Path(mode, color, width, pathID, active);

                        myNetworkPath = path;
                        myNetworkPathPage = page;


                        break;
                    }
                    case Request::ENDPATH:
                    {
                        std::cout << " ENDPATH" << std::endl;

                        //Move this path to the permanent pathsOnPage
                        pathsOnPage[myNetworkPathPage].push_back(myNetworkPath);

                        myNetworkPath = NULL;
                        myNetworkPathPage = -1;

                        break;
                    }
                    case Request::DELETEPATH:
                    {
                        std::cout << " DELETEPATH" << std::endl;
                        break;
                    }
                    case Request::OWNERSHIP:
                    {
                        std::cout << " OWNERSHIP" << std::endl;

                        fileOwner = ( ( OwnershipRequest* ) mRequests->at(i) )->getOwner();
                        break;
                    }
                    case Request::RELEASEOWNERSHIP:
                    {
                        std::cout << " RELEASEOWNERSHIP" << std::endl;
                        break;
                    }
                    case Request::REDO:
                    {
                        std::cout << " REDO" << std::endl;
                        break;
                    }
                    case Request::UNDO:
                    {
                        std::cout << "UNDO " << std::endl;
                        break;
                    }
                    case Request::FILELIST:
                    {
                        std::cout << " FILELIST" << std::endl;
                        break;
                    }
                    case Request::LOGIN:
                    {
                        std::cout << " LOGIN" << std::endl;
                        break;
                    }
                    case Request::LOGOUT:
                    {
                        std::cout << " LOGOUT" << std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout << "SHOULD NEVER GET HERE!!!!!" << std::endl;
                    }

                }
                std::cout << "In request type " << mRequests->at(i)->getRequestType() << "    " << mRequests->at(i)->getRequestID() << std::endl;
                nextRequestID++;

                //Deleting the request and then setting it to NULL so that it can be removed from the vector at the next run
                delete mRequests->at(i);
                mRequests->at(i) = NULL;
            }
        }
        //repeat the 2 above steps until either all requests are met or the nextRequestID does not match the ID of the next request in the queue

        //Repeat the requests each 200 milliseconds
        //std::cout<<"NetworkRequestsAnalyzer"<<std::endl;
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

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

    mySender->NewPath(3, true, 34567, true, 0, 1);
    mySender->AddPoints(3, 4, mPoints);
    mySender->EndPath(3);
    mySender->ReleaseOwnership();
    //mySender->Logout();

    std::cout << "Scribble area end of SendTests function" << std::endl;
}
