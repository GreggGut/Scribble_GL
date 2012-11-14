/* 
 * File:   DeletePathRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 5:05 PM
 */

#ifndef DELETEPATHREQUEST_H
#define	DELETEPATHREQUEST_H

#include "Request.h"

class DeletePathRequest : public Request
{
public:
    DeletePathRequest(int requestID, int page, int pathID);
    virtual ~DeletePathRequest();

    static std::string const requestType()
    {
        return "DeletePathRequest";
    }

    int getPage() const
    {
        return page;
    }

    int getPathID() const
    {
        return pathID;
    }

private:
    int page;
    int pathID;

};

#endif	/* DELETEPATHREQUEST_H */

