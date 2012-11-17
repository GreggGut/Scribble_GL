/* 
 * File:   Request.h
 * Author: scribble
 *
 * Created on November 10, 2012, 3:37 PM
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include <string>
#include <vector>

#include "Point.h"

class Request
{
public:
    Request(int id, int type);
    virtual ~Request();
    int getRequestID();

    int getRequestType()
    {
        return requestType;
    }

    static enum RequestType
    {
        LOGIN=0,
        LOGOUT=1,
        NEWPATH=2,
        ADDPOINTS=3,
        ENDPATH=4,
        UNDO=5,
        REDO=6,
        OWNERSHIP=7,
        RELEASEOWNERSHIP=8,
        DELETEPATH=9,
        FILELIST=10

    } res;
private:
    int requestID;
    int requestType;
};

#endif	/* REQUEST_H */

