/* 
 * File:   LogoutRequest.cpp
 * Author: scribble
 * 
 * Created on November 14, 2012, 10:27 PM
 */

#include "LogoutRequest.h"

LogoutRequest::LogoutRequest(int request) : Request(request, Request::LOGOUT)
{
}

LogoutRequest::~LogoutRequest()
{
}

