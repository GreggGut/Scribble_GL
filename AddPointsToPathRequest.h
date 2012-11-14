/* 
 * File:   AddPointsToPathRequest.h
 * Author: Grzegorz Gut
 *
 * Created on November 10, 2012, 4:49 PM
 */

#ifndef ADDPOINTSTOPATHREQUEST_H
#define	ADDPOINTSTOPATHREQUEST_H

#include "Request.h"

class AddPointsToPathRequest : public Request
{
public:
    //AddPoints - username - requestID++ - pathID - numberOfPoints - Points
    AddPointsToPathRequest(int requestID, int pathID, int numberOfPoints, std::string Points);
    virtual ~AddPointsToPathRequest();

    static std::string const requestType()
    {
        return "AddPointsToPathRequest";
    }
    std::string getPoints() const
    {
        return points;
    }

    int getNumberOfPoints() const
    {
        return numberOfPoints;
    }

    int getPathID() const
    {
        return pathID;
    }

private:
    int pathID;
    int numberOfPoints;
    std::string points;

};

#endif	/* ADDPOINTSTOPATHREQUEST_H */

