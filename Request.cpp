/* 
 * File:   Request.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 3:37 PM
 */

#include "Request.h"

Request::Request(int request)
{
    this->requestID = request;
}

Request::~Request()
{
}

int Request::getRequestID()
{
    return requestID;
}

