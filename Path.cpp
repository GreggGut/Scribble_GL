/*
 * File:   Paths.cpp
 * Author: greg
 *
 * Created on March 3, 2012, 11:55 AM
 */

#include "Path.h"

/** Default constructor
 *
 * @param point
 * @param mode Write/Erase mode. 0 - Write, 1 - Erase
 * @param color QColor representing the color of the pen to be used
 * @param width The width of the pen
 * @param id A unique ID representing the path
 * @param fin Is the point final (presently not in use but could be used for palm correction algorithm)
 * @param active This is used to know if this path is active or not
 *
 * @return A Path object is created
 *
 * The Paths object is composed of:
 * - mode (write/erase)
 * - pen color and width
 * - unique ID
 * - active (enabled/disabled)
 * - vector of *Points.
 *
 * The vector of *Points represents the actual path. Since it is a vector of pointers it needs to be iterated through in to delete all the Point objects
 */
Path::Path(Point* point, int mode, Color color, int width, int id, bool fin/*, bool active*/) : WriteEraseMode(mode), myPenWidth(width), ID(id), active(true), _final(fin), totalLength(0)
{
    mX = point->getX();
    mY = point->getY();
    mPointsVector.push_back(point);
    area = new ScreenAreas();
    area->set(point->getColumn(), point->getRow());

    if (mode == WRITE){
        //std::cout << "WRITE";
        myPenColor = color;
    }

    else if (mode == ERASE){
        ///std::cout << "ERASE";
        myPenColor = Color(255.0,255.0,255.0);
    }
}

Path::Path(int mode, Color color, int width, int ID/*, bool active*/) : WriteEraseMode(mode), myPenWidth(width), ID(ID), active(true), _final(false), totalLength(0)

{
    mX = 0;
    mY = 0;

    if (mode == WRITE){
        std::cout << "WRITE";
        myPenColor = color;
    }

    else if (mode == ERASE){
        std::cout << "ERASE";
        myPenColor = Color(255.0,255.0,255.0);
    }
    //?@?@?@?@?@?
    area = new ScreenAreas();
    area->set(1, 1);
}

/** Paths Copy constructor
 *
 * @param orig Original paths object
 *
 * @return Paths instance copy
 *
 * The return object is a new path object (with the same ID) with the exception of the path points.
 * This object contains a vector of pointers to the original points and therefore special care needs to be taken when deleting this object.
 */
Path::Path(const Path& orig) : WriteEraseMode(orig.WriteEraseMode), myPenWidth(orig.myPenWidth), myPenColor(orig.myPenColor), mPointsVector(NULL), ID(orig.ID), active(orig.active), _final(orig._final), totalLength(orig.totalLength), mX(orig.mX), mY(orig.mY)
{
    area = new ScreenAreas(*orig.area);
}

/**
 * ~Paths Default destructor
 *
 * Deletes all the Points in the vector
 */
Path::~Path()
{
    for (uint i = 0; i < mPointsVector.size(); i++)
    {
        delete mPointsVector[i];
    }
    mPointsVector.clear();

    delete area;
    //std::cout<<"Path "<<this->ID<<" deleted"<<std::endl;
}

/** Add a point to the Path
 *
 * @param point A pointer to a Point
 *
 * Add a new point to the present path.
 */
void Path::addPoint(Point* point)
{
    //std::cout << " from addPOint: " << point->getX() << " " << point->getY() << std::endl;
//    int dX = /*mX*/0 - point->getX();
//    int dY = /*mY*/0 - point->getY();
//    totalLength += sqrt(dX * dX + dY * dY);
//    area->set(point->getColumn(), point->getRow());
    mPointsVector.push_back(point);
}

/** Get the path
 *
 * @return vector<Point*> A vector of Point pointers
 */
std::vector<Point*> Path::getPath()
{
    return mPointsVector;
}

/** Get pen width
 *
 * @return penWidth An integer representing the pen width
 *
 * This function returns the width of the pen used to draw the current path.
 */
int Path::getPenWidth()
{
    return myPenWidth;
}

/** Get pen color
 *
 * @return Color A QColor representing the current path color
 *
 * This function returns a QColor representing the color on he current path
 */
Color Path::getPenColor() const
{
    return myPenColor;
}

int Path::getPenColorInt()
{
    int rgb = myPenColor.getRed()*255;
    rgb = ( rgb << 8 ) + myPenColor.getGreen()*255;
    rgb = ( rgb << 8 ) + myPenColor.getBlue()*255;
    return rgb;
}

/** Get path mode
 *
 * @return  Mode An integer representing a Write/Erase mode
 *
 * This function returns the mode of the current path. It can be either write or erase:
 * - 0: Write
 * - 1: Erase
 *
 * <b>Should create a ENUM with only 2 options: Write and Erase</b>
 */
int Path::getMode() const
{
    return WriteEraseMode;
}

/**Set path to Erase mode
 *
 * The current path will be set to erase mode.
 */
void Path::setEraseMode()
{
    WriteEraseMode = ERASE;
}

/** Set path to Write mode
 *
 * The current path will be set to write mode.
 */
void Path::setWriteMode()
{
    WriteEraseMode = WRITE;
}

/** Get path ID
 *
 * @return ID The current path ID
 *
 * Each path has an unique ID and it can be obtained using this function. The ID corresponds to a collection of points regardless of its mode.
 */
int Path::getPathID() const
{
    return ID;
}

/** Get total length of the path
 *
 * @return The total length of the path
 */
int Path::getLength()
{
    return totalLength;
}

/** Disable current path
 *
 * This function is used to disable a path. A disable path means that there is a more up to date version of this path so that this one is not used. Needed for rendering.
 *
 * An old copy of the path is used in the case the user would undo a change to a more recent version of a path.
 */
void Path::disablePath()
{
    active = false;
}

/** Enable current path
 *
 * This function is used to enable a path. An enabled path means that this is the most up to date path and it needs to be used whenever rendering.
 */
void Path::enablePath()
{
    active = true;
}

/** Is the current path enabled
 *
 * @return Enabled Return true is the path is enabled
 *
 * This function allows the user to know if the current path is enabled or not.
 */
bool Path::isEnabled() const
{
    return active;
}

/** Square root of an integer
 *
 * @param x The integer that we need the square root of
 * @return The square root of the x parameter
 *
 * This function is about 5 times faster than the sqrt() on the cmath library. It is less precise however this is not an issue in our case
 */
inline int Path::sqrt(const int x)
{

    union
    {
        int i;
        float x;
    } u;
    u.x = x;
    u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
    return u.x;
}

/** Get area
 *
 * @return The area on which the currents path has been drawn
 */
ScreenAreas* Path::getArea()
{
    return area;
}

/**
 *
 * @param color The new QColor of the pen
 */
void Path::setPenColor(Color color)
{
    myPenColor = color;
}

/** Get points count
 *
 * @return The total number of points present in the current path
 */
int Path::getPointsCount()
{
    return mPointsVector.size();
}

int * Path::pointsArray(){

    int vertexs[2*mPointsVector.size()];

    for (int i = 0; i<mPointsVector.size(); ++i){
        *(vertexs + 2*i) = mPointsVector.at(i)->getX();
        *(vertexs + 2*(i+1)) = mPointsVector.at(i)->getY();
    }

}