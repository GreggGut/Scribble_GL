/* 
 * File:   RedoRequest.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 5:04 PM
 */

#include "RedoRequest.h"

RedoRequest::RedoRequest(int request, int page, int pathID) : Request(request)
{
    this->page = page;
    this->pathID = pathID;
}

RedoRequest::~RedoRequest()
{
}

