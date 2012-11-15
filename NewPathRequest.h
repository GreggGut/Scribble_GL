/* 
 * File:   NewPathRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 3:46 PM
 */

#ifndef NEWPATHREQUEST_H
#define	NEWPATHREQUEST_H

#include "Request.h"
#include "Color.h"

class NewPathRequest : public Request
{
public:
    //requestID - pathID - mode - color - active - page
    NewPathRequest(int requestID, int pathID, bool mode, Color color, bool active, int page, int width);
    virtual ~NewPathRequest();

    int getPathID() const
    {
        return pathID;
    }

    bool isActive() const
    {
        return active;
    }

    Color getColor() const
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

    int getWidth() const
    {
        return width;
    }

private:
    int pathID;
    bool mode;
    Color color;
    bool active;
    int page;
    int width;

};

#endif	/* NEWPATHREQUEST_H */

