/* 
 * File:   NewPathRequest.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 3:46 PM
 */

#include "NewPathRequest.h"

NewPathRequest::NewPathRequest(int request, int pathID, bool mode, int color, bool active, int page) : Request(request)
{
    this->pathID = pathID;
    this->mode = mode;
    this->color = color;
    this->active = active;
    this->page = page;
}

NewPathRequest::~NewPathRequest()
{
}

