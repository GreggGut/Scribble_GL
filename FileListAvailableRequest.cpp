/* 
 * File:   FileListAvailableRequest.cpp
 * Author: scribble
 * 
 * Created on November 13, 2012, 3:44 PM
 */

#include "FileListAvailableRequest.h"

//TODO request ID
FileListAvailableRequest::FileListAvailableRequest(int reqID, std::string files): Request(reqID, Request::FILELIST)
{
    this->files=files;
}

FileListAvailableRequest::~FileListAvailableRequest()
{
}

