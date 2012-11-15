/* 
 * File:   Request.h
 * Author: scribble
 *
 * Created on November 10, 2012, 3:37 PM
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include <string>

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
        LOGIN,
        LOGOUT,
        NEWPATH,
        ADDPOINTS,
        ENDPATH,
        UNDO,
        REDO,
        OWNERSHIP,
        RELEASEOWNERSHIP,
        DELETEPATH,
        FILELIST

    } res;
private:
    int requestID;
    int requestType;
};

#endif	/* REQUEST_H */

