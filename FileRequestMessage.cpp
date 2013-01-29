#include "FileRequestMessage.h"

FileRequestMessage::FileRequestMessage() : body_length_(0)
{
}

char* FileRequestMessage::data()
{
    return data_;
}

size_t FileRequestMessage::length()
{
    return body_length_;
}

char* FileRequestMessage::body()
{
    return data_;
}

size_t FileRequestMessage::body_length()
{
    return body_length_;
}

void FileRequestMessage::body_length(size_t length)
{
    body_length_ = length;
    if ( body_length_ > max_body_length )
        body_length_ = max_body_length;
}