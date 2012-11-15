/* 
 * File:   OwnershipRequest.cpp
 * Author: scribble
 * 
 * Created on November 13, 2012, 3:15 PM
 */

#include "OwnershipRequest.h"

OwnershipRequest::OwnershipRequest(int request, std::string username, int nextRequestID) : Request(request, Request::OWNERSHIP)
{
    this->username = username;
    this->nextRequestID = nextRequestID;
}

OwnershipRequest::~OwnershipRequest()
{
}

