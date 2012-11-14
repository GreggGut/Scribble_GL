/* 
 * File:   UndoRequest.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 5:04 PM
 */

#include "UndoRequest.h"

UndoRequest::UndoRequest(int request, int page, int pathID) : Request(request)
{
    this->page = page;
    this->pathID = pathID;
}

UndoRequest::~UndoRequest()
{
}

