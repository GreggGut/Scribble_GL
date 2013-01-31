/*
 * File:   RequestMessage.h
 * Author: scribble
 *
 * Created on November 25, 2012, 11:27 AM
 */

#ifndef REQUESTMESSAGE_H
#define	REQUESTMESSAGE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class RequestMessage
{
public:

    enum
    {
        header_length = 4
    };

    enum
    {
        max_body_length =  512
    };

    RequestMessage();

    const char* data() const
    {
        return data_;
    }
    char* data();
    size_t length();

    const char* body() const
    {
        return data_ + header_length;
    }
    char* body();
    size_t body_length();
    void body_length(size_t length);
    bool decode_header();
    void encode_header();

private:
    char data_[header_length + max_body_length];
    size_t body_length_;
};

#endif	/* REQUESTMESSAGE_H */

