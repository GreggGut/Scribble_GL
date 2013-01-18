/* 
 * File:   Points.cpp
 * Author: greg
 * 
 * Created on January 14, 2012, 3:03 PM
 */

#include <sstream>

#include "Point.h"
#include "Color.h"

/*! Default constructor
 * \param Column An integer representing the column in which the point exists
 * \param Row An integer representing the row in which the point exists
 * \param x The X coordinates of the point
 * \param y The Y coordinates of the point
 * 
 * This is the default constructor of the point object. 
 */
Point::Point(int column_, int row_, int x_, int y_)
{
    //x(WIDTH-x-15), y(y-21), column(Column), row(Row
    
    x = WIDTH-x_-15;
    y = y_-15;
    column = column_;
    row = row_;
    
//    /WIDTH-QPoint::y()-10;
    //For testing purpose
    //printf(" Added point: %x, %x, %x, %x", this->column, this->row, this->x(), this->y());
    //std::cout<<"Added point: "<<this->x()<<" "<<this->y()<<std::endl;
}

Point::Point(int x_, int y_){
     x = x_;
    y = y_;
    column = 0;
    row = 0;
}

/*! Copy constructor
 * \param orig A reference to the original point that needs to be copied
 * 
 * This is a copy constructor. It takes an Point object and creates an exact copy of it
 */
Point::Point(const Point& orig) : x(orig.x), y(orig.y), column(orig.column), row(orig.row)   //orig.x(), orig.y()
{

}

/*! Constructor
 * 
 * This constructor is needed because ??????????????????????????
 */
Point::Point() : x(0), y(0),column(0), row(0)
{

}

/*! Default destructor
 * 
 * This is the default destructor. The object does not use any pointer and therefore the destructor is empty for now.
 */
Point::~Point()
{
}

//Getters

/*! Get column
 * 
 * \return <i>Column</i> - An integer representing the column in which the point exists
 */
int Point::getColumn() const
{
    return column;
}

/*! Get row
 * 
 * \returns <i>Row</i> - An integer representing the row n which the point exists
 */
int Point::getRow() const
{
    return row;
}

int Point::getX() {
    return x;
}

int Point::getY(){
    return y;
}

void Point::setX(int x_) {
    x = x_;
}

void Point::setY(int y_){
    y = y_;
}

void Point::adjustForSaving()
{
    //819, 1092
    //768, 1024
    x = ((x-33)*819/WIDTH);
    y = ((y-33)*1092/HEIGHT);
}