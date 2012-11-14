/* 
 * File:   FileListAvailableRequest.cpp
 * Author: scribble
 * 
 * Created on November 13, 2012, 3:44 PM
 */

#include "FileListAvailableRequest.h"

FileListAvailableRequest::FileListAvailableRequest(std::string files): Request(-1)
{
    this->files=files;
}

FileListAvailableRequest::~FileListAvailableRequest()
{
}

