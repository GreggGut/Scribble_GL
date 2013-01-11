/*
 * File:   ScribbleArea.cpp
 * Author: scribble
 *
 * Created on October 25, 2012, 2:17 PM
 */

#include "ScribbleArea.h"
#include "Sender.h"

ScribbleArea::ScribbleArea() : networkPathPage(-1)
{

    penColor = Color();
    penSize = 1.0;
    currentPage = 0;

    pathsOnPage.resize(5);
    Paths_IDs.resize(5);
    redoVector.resize(5);
}

ScribbleArea::ScribbleArea(int x, int y, int w, int h) : networkPathPage(-1)
{

    xPos = x;
    yPos = y;
    width = w;
    height = h;

    penColor = Color();
    penSize = 1.0;
    currentPage = 0;

    pathsOnPage.resize(5);
    Paths_IDs.resize(5);
    redoVector.resize(5);
}

ScribbleArea::ScribbleArea(const ScribbleArea& orig)
{
}

ScribbleArea::~ScribbleArea()
{

    delete mTempPath;
    if ( mNetworkPath != NULL )
    {
        delete mNetworkPath;
    }
}

Color ScribbleArea::getPenColor()
{
    return penColor;
}

float ScribbleArea::getPenSize()
{
    return penSize;
}

void ScribbleArea::setPenColor(Color &newColor)
{
    penColor = newColor;
}

/*! Set Pen Width
 *
 * \param newWidth An integer representing the new width of the pen
 *
 * This function set the width of the pen to be used.
 */
void ScribbleArea::setPenWidth(int newWidth)
{
    penSize = newWidth;
}

int ScribbleArea::getMode()
{

    return mMode;
}

std::vector<std::vector<Path*> > ScribbleArea::getPathsOnPage()
{
    return pathsOnPage;
}

int ScribbleArea::getCurrentPage()
{
    return currentPage;
}

void ScribbleArea::setLockForTempPath(bool lock)
{

    if ( lock == 1 )
    {
        lockForTempPath.lock();
    }

    else
    {
        lockForTempPath.unlock();
    }
}

void ScribbleArea::setLockForPath(bool lock)
{

    if ( lock == 1 )
    {
        pathsLock.lock();
    }

    else
    {
        pathsLock.unlock();
    }
}

void ScribbleArea::setLockForNetworkPath(bool lock)
{

    if ( lock == 1 )
    {
        lockForNetworkPath.lock();
    }

    else
    {
        lockForNetworkPath.unlock();
    }
}

Path* ScribbleArea::getTempPath()
{
    return mTempPath;
}

Path* ScribbleArea::getNetworkPath()
{
    return mNetworkPath;
}

int ScribbleArea::getNetworkPage()
{
    return networkPathPage;
}

bool ScribbleArea::pointInsideArea(Point * point)
{

    //point has to be inside frame. could be changed but overlaps may occur
    if ( ( point->getX() > xPos ) && ( point->getX() < width + xPos ) && ( point->getY() > yPos ) && ( point->getY() < height + yPos ) )
    {
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
        //TOTEST
        sender->sendNewPath(mTempPath->getPathID(), mMode, mTempPath->getPenColorInt()/*, mTempPath->isEnabled()*/, currentPage, penSize);
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
        //TOTEST
        sender->sendPoints(point);
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
            //TOCONF is this how we want to do this part? send end of path and then delete it?
            //TOTEST
            sender->sendEndPath();
            sender->sendDeletePath(currentPage, mTempPath->getPathID());
            delete mTempPath;
        }
        else
        {
            pathsOnPage.at(currentPage).push_back(mTempPath);
            //TOTEST
            sender->sendEndPath();
        }

        mTempPath = NULL;

        lockForTempPath.unlock();
        pathsLock.unlock();
    }
    else
    {

    }
}

/*! Undo
 *
 * This function allows the user to undo the last actions. Presently, there is no limit of now many undo can be performed, meaning the user can press undo until there is nothing present on the screen
 */
void ScribbleArea::undo()
{
    pathsLock.lock();
    if ( !pathsOnPage.at(currentPage).empty() )
    {
        for ( int i = ( int ) pathsOnPage.at(currentPage).size() - 1; i >= 0; i-- )
        {
            if ( pathsOnPage.at(currentPage).at(i) != NULL )
            {
                redoVector.at(currentPage).push_back(pathsOnPage.at(currentPage).at(i));

                int id = pathsOnPage.at(currentPage).at(i)->getPathID();
                //pathsOnPage.at(currentPage).at(i) = NULL; //pop_back();

                pathsOnPage.at(currentPage).pop_back();
                
                for ( int j = i - 1; j >= 0; j-- )
                {
                    if ( pathsOnPage.at(currentPage).at(j) != NULL && id == pathsOnPage.at(currentPage).at(j)->getPathID() )
                    {
                        pathsOnPage.at(currentPage).at(j)->enablePath();
                        break;
                    }
                }
                break;
            }
        }
    }
    //TODO This needs to be called only if the undo button was touched and not when received by network
    //sender->sendUndo(currentPage);
    pathsLock.unlock();
}

/*! Redo
 *
 * This function allows the user to redo the last undone actions. This action is only available if the last action(s) is an undo, otherwise this function will have no effect
 */
void ScribbleArea::redo()
{
    pathsLock.lock();
    if ( !redoVector.at(currentPage).empty() )
    {
        int id = redoVector.at(currentPage).back()->getPathID();
        for ( int i = pathsOnPage.at(currentPage).size() - 1; i >= 0; i-- )
        {
            if ( pathsOnPage.at(currentPage).at(i) != NULL && id == pathsOnPage.at(currentPage).at(i)->getPathID() )
            {
                //std::cout << "Redone Path " << id << std::endl;
                pathsOnPage.at(currentPage).at(i)->disablePath();
                break;
            }
        }

        pathsOnPage.at(currentPage).push_back(redoVector.at(currentPage).back());
        redoVector.at(currentPage).pop_back();

        //TOCONF For now I think we should resend the redone path to the server so that the server has the path in memory
        //TODO implement the network redo
    }
    pathsLock.unlock();
}

/*! Set write mode
 *
 * This function set the mode to write, allowing the user to write on top of the PDF
 */
void ScribbleArea::write()
{
    mMode = WRITE;
}

/*! Set erase mode
 *
 * This function set the mode to erase, allowing the user to erase anything that has been written on top of the PDF, leaving the PDF intact
 */
void ScribbleArea::erase()
{
    mMode = ERASE;
}

/*! Clear all
 *
 * This function clears the current page from all writing. This action <b>cannot</b> be undone.
 */
void ScribbleArea::clearAll()
{
    cleanRedoVector();
    cleanPathsOnCurentPageVector();

    Paths_IDs[currentPage] = 0;
    //TOTEST
    sender->sendCleanAll(currentPage);

    //updatePDF();
    //lockForImage.lock();
    //image = imageCopy.copy();
    //lockForImage.unlock();
    //updatePageContent();

}

/*! Clean Redo Vector (Delete all objects)
 *
 * This function iterates through the Redo vector, compares all paths to the paths in PathOnPages vector while deleting only the points that are only present in the Redo vector.
 * Otherwise the vector of points is cleared and then the Path object deleted
 */
void ScribbleArea::cleanRedoVector()
{
    int redoVecSize = ( int ) redoVector.at(currentPage).size();

    //For each Path in redoVector, find if the same path ID is present on the current page of PathsOnPage
    //If present then clear the points vector and then delete the Path object
    //Otherwise delete delete Path without cleaning it which will delete all Point objects
    for ( int i = 0; i < redoVecSize; i++ )
    {
        delete redoVector.at(currentPage).at(i);
        redoVector.at(currentPage).at(i) = NULL;
    }

    redoVector.at(currentPage).clear();
}

/*! Clean PathOnPageVector (Delete all objects)
 *
 * This functions cleans all the path object present in the vector. Since the Point objects are shared it makes sure that it is deleted only once
 */
void ScribbleArea::cleanPathsOnCurentPageVector()
{
    pathsLock.lock();
    int vectorSize = pathsOnPage.at(currentPage).size();

    for ( int i = 0; i < vectorSize; i++ )
    {
        delete pathsOnPage.at(currentPage).at(i);
        pathsOnPage.at(currentPage).at(i) = NULL;
    }

    pathsOnPage.at(currentPage).clear();
    pathsLock.unlock();

    //delete[] deleted;
}

void ScribbleArea::Draw()
{
    glColor3f(penColor.getRed(), penColor.getGreen(), penColor.getBlue());

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
    if ( mTempPath != NULL )
    {
        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < mTempPath->getPath().size(); ++j )
        {

            glVertex3f(mTempPath->getPath().at(j)->getX(), mTempPath->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    lockForTempPath.unlock();

    lockForNetworkPath.lock();
    if ( currentPage == networkPathPage && mNetworkPath != NULL )
    {
        glBegin(GL_LINE_STRIP);
        for ( int j = 0; j < mNetworkPath->getPath().size(); ++j )
        {

            glVertex3f(mNetworkPath->getPath().at(j)->getX(), mNetworkPath->getPath().at(j)->getY(), 0.0f);
        }

        glEnd();
    }
    lockForNetworkPath.unlock();


}

void ScribbleArea::setNetworkPage(int p)
{
    lockForNetworkPath.lock();
    std::cout << "Setting network page: " << p << std::endl;
    networkPathPage = p;
    lockForNetworkPath.unlock();
}

void ScribbleArea::setNetworkPath(Path* p)
{
    lockForNetworkPath.lock();
    mNetworkPath = p;
    lockForNetworkPath.unlock();
}

void ScribbleArea::addNetworkPoint(Point * p)
{
    lockForNetworkPath.lock();
    mNetworkPath->addPoint(p);
    lockForNetworkPath.unlock();
}

void ScribbleArea::endNetworkPath()
{
    pathsLock.lock();
    lockForNetworkPath.lock();
    pathsOnPage.at(networkPathPage).push_back(mNetworkPath);
    mNetworkPath = NULL;
    //TOCONF This could be done more efficiently by sending the page number only on page changes and not with each new path, undo, redo, delete... and so on
    networkPathPage = -1;
    lockForNetworkPath.unlock();
    pathsLock.unlock();
}

void ScribbleArea::setSender(Sender* sender)
{
    this->sender = sender;
}