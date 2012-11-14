/* 
 * File:   OwnershipRequest.h
 * Author: scribble
 *
 * Created on November 13, 2012, 3:15 PM
 */

#ifndef OWNERSHIPREQUEST_H
#define	OWNERSHIPREQUEST_H

#include "Request.h"

class OwnershipRequest : public Request
{
public:
    OwnershipRequest(int request, std::string username, int nextRequestID);
    virtual ~OwnershipRequest();
private:
    std::string username;
    int nextRequestID;

};

#endif	/* OWNERSHIPREQUEST_H */

