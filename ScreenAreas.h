/*
 * File:   screenAreas.h
 * Author: greg
 *
 * Created on May 28, 2012, 3:16 PM
 */

#ifndef SCREENAREAS_H
#define	SCREENAREAS_H

#include "defines.h"
#include <iostream>
#include <bitset>
#include <stdlib.h>

class ScreenAreas
{
public:
    ScreenAreas();
    ScreenAreas(const ScreenAreas& orig);
    virtual ~ScreenAreas();
    void clearMatrix();
    bool set(int Column, int Row);
    bool reset(int Column, int Row);
    bool isSet(int Column, int Row);
    bool isSet();
    bool setArea(int Column, int Row);
    bool resetArea(int Column, int Row);
    bool possiblePen(int Column, int Row);
    
    static void orAreas(ScreenAreas*,ScreenAreas*);
    static bool overlap(ScreenAreas*, ScreenAreas*);
    
    void printMatrix();

private:
    short R[N_ROW];
};

#endif	/* SCREENAREAS_H */

