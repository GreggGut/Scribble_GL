/* 
 * File:   ScribbleArea.cpp
 * Author: scribble
 * 
 * Created on October 25, 2012, 2:17 PM
 */

#include "ScribbleArea.h"
#include "Sender.h"

ScribbleArea::ScribbleArea(): networkPathPage(-1) {

    penColor = Color();
    penSize = 1.0;
    currentPage = 0;

    pathsOnPage.resize(5);
    Paths_IDs.resize(5);
    redoVector.resize(5);
}

ScribbleArea::ScribbleArea(int x_, int y_, int w_, int h_) : networkPathPage(-1){

    mMode = WRITE;
    x = x_;
    y = y_;
    width = w_;
    height = h_;

    penColor = Color();
    penSize = 1.0;
    currentPage = 0;
    mTempPath = NULL;

    pathsOnPage.resize(5);
    Paths_IDs.resize(5);
    redoVector.resize(5);
}

ScribbleArea::ScribbleArea(const ScribbleArea& orig) {
}

ScribbleArea::~ScribbleArea() {

    delete mTempPath;
}

Color ScribbleArea::getPenColor() {
    return penColor;
}

float ScribbleArea::getPenSize() {
    return penSize;
}

void ScribbleArea::setPenColor(Color &newColor) {
    penColor = newColor;
}

/*! Set Pen Width
 *
 * \param newWidth An integer representing the new width of the pen
 *
 * This function set the width of the pen to be used.
 */
void ScribbleArea::setPenWidth(int newWidth) {
    penSize = newWidth;
}

int ScribbleArea::getMode() {

    return mMode;
}

void ScribbleArea::setMode(int mode) {

    mMode = mode;
}

std::vector<std::vector<Path*> > ScribbleArea::getPathsOnPage() {
    return pathsOnPage;
}

int ScribbleArea::getCurrentPage() {
    return currentPage;
}

void ScribbleArea::setLockForPath(bool lock) {

    if (lock == 1) {
        lockForTempPath.lock();
    } else {
        lockForTempPath.unlock();
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

Path* ScribbleArea::getTempPath() {
    return mTempPath;
}

bool ScribbleArea::pointInsideArea(Point * point) {

    //point has to be inside frame. could be changed but overlaps may occur
    if ((point->getX() > x) && (point->getX() < width + x) && (point->getY() > y) && (point->getY() < height + y)) {
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
void ScribbleArea::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

    //If mode is write, initialize the writing sequence
    if (this->mMode == WRITE) {
        //cleanRedoVector();
        lastPoint.setX(point->getX());
        lastPoint.setY(point->getY());
        scribbling = true;

        lockForTempPath.lock();
        mTempPath = new Path(point, this->mMode, this->penColor, this->penSize, Paths_IDs[currentPage]++);
        //TOTEST
        sender->sendNewPath(mTempPath->getPathID(), mMode, mTempPath->getPenColorInt()/*, mTempPath->isEnabled()*/, currentPage, penSize);

        lockForTempPath.unlock();
    }        //any other point needs to be delete
    else {
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
void ScribbleArea::screenMoveEvent(Point* point) {
    if (point == NULL) {
        return;
    }
    if (scribbling == true) {
        pathsLock.lock();
        lockForTempPath.lock();
        mTempPath->addPoint(point);
        sender->sendPoints(point);
        lockForTempPath.unlock();
        pathsLock.unlock();
    }//Here we can add more else if to enhance user experience by changing the color of the pressed button.
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
    if (scribbling == true)
    {
        scribbling = false;

        pathsLock.lock();
        lockForTempPath.lock();

        if (mTempPath != NULL)
        {

            pathsOnPage.at(currentPage).push_back(mTempPath);
            sender->sendEndPath();

            mTempPath = NULL;
        }

        lockForTempPath.unlock();
        pathsLock.unlock();

    } else
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

    if (!pathsOnPage.at(currentPage).empty())
    {

        if (!redoVector.at(currentPage).empty())
        {
            if (pathsOnPage.at(currentPage).back()->getPathID() > redoVector.at(currentPage).back()->getPathID())
            {
                redoVector.at(currentPage).clear();
            }
        }
        redoVector.at(currentPage).push_back(pathsOnPage.at(currentPage).back());
        pathsOnPage.at(currentPage).pop_back();

        //updatePageContent();
    }

    pathsLock.unlock();
}

/*! Redo
 *
 * This function allows the user to redo the last undone actions. This action is only available if the last action(s) is an undo, otherwise this function will have no effect
 */
void ScribbleArea::redo()
{

    pathsLock.lock();
    if (!redoVector.at(currentPage).empty())
    {

        pathsOnPage.at(currentPage).push_back(redoVector.at(currentPage).back());
        redoVector.at(currentPage).pop_back();

        //updatePageContent();
    }
    pathsLock.unlock();
}

/*! Clear all
 *
 * This function clears the current page from all writing. This action <b>cannot</b> be undone.
 */
void ScribbleArea::clearAll()
{

    pathsLock.lock();
    if (!pathsOnPage.at(currentPage).empty())
    {

        //redoVector.at(currentPage).insert(redoVector.at(currentPage).end(), pathsOnPage.at(currentPage).begin(), pathsOnPage.at(currentPage).end());
        pathsOnPage.at(currentPage).clear();

        //updatePageContent();
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

bool ScribbleArea::getScribbling()
{
    return scribbling;
}

void ScribbleArea::setNetworkPage(int p)
{
    lockForNetworkPath.lock();
    std::cout << "Setting network page: " << p << std::endl;
    networkPathPage = p;
    lockForNetworkPath.unlock();
}

Path* ScribbleArea::getNetworkPath()
{
    return mNetworkPath;
}

int ScribbleArea::getNetworkPage()
{
    return networkPathPage;
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

Sender* ScribbleArea::getSender()
{
    return sender;
}