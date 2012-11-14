/* 
 * File:   NewPathRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 3:46 PM
 */

#ifndef NEWPATHREQUEST_H
#define	NEWPATHREQUEST_H

#include "Request.h"

class NewPathRequest : public Request
{
public:
    //requestID - pathID - mode - color - active - page
    NewPathRequest(int requestID, int pathID, bool mode, int color, bool active, int page);
    virtual ~NewPathRequest();

    static std::string const requestType()
    {
        return "NewPathRequest";
    }

    int getPathID() const
    {
        return pathID;
    }

    bool isActive() const
    {
        return active;
    }

    int getColor() const
    {
        return color;
    }

    bool isMode() const
    {
        return mode;
    }

    int getPage() const
    {
        return page;
    }

private:
    int pathID;
    bool mode;
    int color;
    bool active;
    int page;

};

#endif	/* NEWPATHREQUEST_H */

