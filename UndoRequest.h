/* 
 * File:   UndoRequest.h
 * Author: scribble
 *
 * Created on November 10, 2012, 5:04 PM
 */

#ifndef UNDOREQUEST_H
#define	UNDOREQUEST_H

#include "Request.h"

class UndoRequest : public Request
{
public:
    UndoRequest(int requestID, int page, int pathID);
    virtual ~UndoRequest();

    static std::string const requestType()
    {
        return "UndoRequest";
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

#endif	/* UNDOREQUEST_H */

