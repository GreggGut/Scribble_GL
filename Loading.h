/* 
 * File:   Loading.h
 * Author: scribble
 *
 * Created on March 26, 2013, 6:47 AM
 */

#ifndef LOADING_H
#define	LOADING_H

#include <string>
#include "defines.h"

class Loading {
public:
    Loading();
    Loading(const Loading& orig);
    virtual ~Loading();
    std::string getTopRing();
    std::string getBottomRing();
    std::string getBackground();
    int getTopAngle();
    int getBottomAngle();
    void setTopAngle();
    void setBottomAngle();
    void reset();
    
private:
    int topAngle;
    int bottomAngle;
    
    std::string topRing;
    std::string bottomRing;
    std::string background; 
};

#endif	/* LOADING_H */

