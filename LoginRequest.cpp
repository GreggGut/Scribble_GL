/* 
 * File:   LoginRequest.cpp
 * Author: scribble
 * 
 * Created on November 13, 2012, 9:24 PM
 */

#include "LoginRequest.h"

LoginRequest::LoginRequest(int request) : Request(request, Request::LOGIN)
{
}

LoginRequest::~LoginRequest()
{
}

