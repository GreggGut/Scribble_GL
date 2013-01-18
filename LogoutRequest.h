/* 
 * File:   LogoutRequest.h
 * Author: scribble
 *
 * Created on November 14, 2012, 10:27 PM
 */

#ifndef LOGOUTREQUEST_H
#define	LOGOUTREQUEST_H

#include "Request.h"


class LogoutRequest: public Request
{
public:
    LogoutRequest(int request);
    virtual ~LogoutRequest();
private:

};

#endif	/* LOGOUTREQUEST_H */

