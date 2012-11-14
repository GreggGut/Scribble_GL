/* 
 * File:   DeletePathRequest.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 5:05 PM
 */

#include "DeletePathRequest.h"

DeletePathRequest::DeletePathRequest(int request, int page, int pathID) : Request(request)
{
    this->page = page;
    this->pathID = pathID;
}

DeletePathRequest::~DeletePathRequest()
{
}

