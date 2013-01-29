/*
 * File:   RequestMessage.h
 * Author: scribble
 *
 * Created on November 25, 2012, 11:27 AM
 */

#ifndef FILEREQUESTMESSAGE_H
#define	FILEREQUESTMESSAGE_H

#include <cstdio> 
#include <cstdlib>
#include <cstring>

class FileRequestMessage
{
public:

    enum
    {
        max_body_length = 512
    };

    FileRequestMessage();

    const char* data() const
    {
        return data_;
    }
    char* data();
    size_t length();

    const char* body() const
    {
        return data_;
    }
    char* body();
    size_t body_length();
    void body_length(size_t length);

private:
    char data_[max_body_length];
    size_t body_length_;
};

#endif	/* FILEREQUESTMESSAGE_H */

