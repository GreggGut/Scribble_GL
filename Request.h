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
    Request(int);
    virtual ~Request();
    int getRequestID();
    static std::string const requestType()
    {
        return "none";
    }
private:
    int requestID;

};

#endif	/* REQUEST_H */

