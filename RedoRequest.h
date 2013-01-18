/* 
 * File:   RedoRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 5:04 PM
 */

#ifndef REDOREQUEST_H
#define	REDOREQUEST_H

#include "Request.h"

class RedoRequest : public Request
{
public:
    RedoRequest(int requestID, int page, int pathID);
    virtual ~RedoRequest();

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

#endif	/* REDOREQUEST_H */

