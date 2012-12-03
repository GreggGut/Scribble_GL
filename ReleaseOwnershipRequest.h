/* 
 * File:   ReleaseOwnershipRequest.h
 * Author: scribble
 *
 * Created on November 17, 2012, 12:47 PM
 */

#ifndef RELEASEOWNERSHIPREQUEST_H
#define	RELEASEOWNERSHIPREQUEST_H

#include "Request.h"


class ReleaseOwnershipRequest: public Request
{
public:
    ReleaseOwnershipRequest(int reqID);
    virtual ~ReleaseOwnershipRequest();
private:

};

#endif	/* RELEASEOWNERSHIPREQUEST_H */

