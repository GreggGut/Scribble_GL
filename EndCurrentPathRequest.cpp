/* 
 * File:   EndCurrentPathRequest.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 5:02 PM
 */

#include "EndCurrentPathRequest.h"

EndCurrentPathRequest::EndCurrentPathRequest(int request, int pathID):Request(request)
{
    this->pathID=pathID;
}


EndCurrentPathRequest::~EndCurrentPathRequest()
{
}

