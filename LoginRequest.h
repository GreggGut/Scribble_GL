/* 
 * File:   LoginRequest.h
 * Author: scribble
 *
 * Created on November 13, 2012, 9:24 PM
 */

#ifndef LOGINREQUEST_H
#define	LOGINREQUEST_H

#include "Request.h"

class LoginRequest : public Request
{
public:
    LoginRequest(int reqID);

    virtual ~LoginRequest();
private:

};

#endif	/* LOGINREQUEST_H */

