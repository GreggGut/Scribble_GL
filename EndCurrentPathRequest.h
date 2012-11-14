/* 
 * File:   EndCurrentPathRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 5:02 PM
 */

#ifndef ENDCURRENTPATHREQUEST_H
#define	ENDCURRENTPATHREQUEST_H

#include "Request.h"

class EndCurrentPathRequest : public Request
{
public:
    EndCurrentPathRequest(int requestID, int pathID);
    virtual ~EndCurrentPathRequest();

    static std::string const requestType()
    {
        return "EndCurrentPathRequest";
    }

    int getPathID() const
    {
        return pathID;
    }

private:
    int pathID;

};

#endif	/* ENDCURRENTPATHREQUEST_H */

