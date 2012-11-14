/* 
 * File:   FileListAvailableRequest.h
 * Author: scribble
 *
 * Created on November 13, 2012, 3:44 PM
 */

#ifndef FILELISTAVAILABLEREQUEST_H
#define	FILELISTAVAILABLEREQUEST_H

#include "Request.h"


class FileListAvailableRequest:  public Request
{
public:
    FileListAvailableRequest(/*int reqID,*/ std::string files);
    virtual ~FileListAvailableRequest();
private:
    std::string files;

};

#endif	/* FILELISTAVAILABLEREQUEST_H */

