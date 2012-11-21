/* 
 * File:   AddPointsToPathRequest.cpp
 * Author: Grzegorz Gut
 * 
 * Created on November 10, 2012, 4:49 PM
 */

#include "AddPointsToPathRequest.h"

AddPointsToPathRequest::AddPointsToPathRequest(int request, int pathID, int numberOfPoints, std::vector<Point *>* mPoints): Request(request,Request::ADDPOINTS)
{
    this->pathID=pathID;
    this->numberOfPoints=numberOfPoints;
    this->mPoints=mPoints;
}

AddPointsToPathRequest::~AddPointsToPathRequest()
{
}

