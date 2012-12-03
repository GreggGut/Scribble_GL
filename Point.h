/* 
 * File:   Points.h
 * Author: greg
 *
 * Created on January 14, 2012, 3:03 PM
 */

#ifndef POINTS_H
#define	POINTS_H

#include "defines.h"
#include <iostream>

class Point{
    
public:
    explicit Point(int column_, int row_, int x_, int y_);
    Point(int x_, int y_);
   
    Point(const Point& orig);
    Point();
    virtual ~Point();

    //Getters
    int getColumn() const;
    int getRow() const;
    void adjustForSaving();
    int getX();
    int getY();
    void setX(int x_);
    void setY(int y_);
    
private:
    int x;
    int y;
    int column;
    int row;
};

#endif	/* POINTS_H */


