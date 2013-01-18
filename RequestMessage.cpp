#include "RequestMessage.h"

RequestMessage::RequestMessage() : body_length_(0)
{
}

char* RequestMessage::data()
{
    return data_;
}

size_t RequestMessage::length()
{
    return header_length + body_length_;
}

char* RequestMessage::body()
{
    return data_ + header_length;
}

size_t RequestMessage::body_length()
{
    return body_length_;
}

void RequestMessage::body_length(size_t length)
{
    body_length_ = length;
    if ( body_length_ > max_body_length )
        body_length_ = max_body_length;
}

bool RequestMessage::decode_header()
{
    char header[header_length + 1] = "";
    std::strncat(header, data_, header_length);
    body_length_ = std::atoi(header);
    if ( body_length_ > max_body_length )
    {
        body_length_ = 0;
        return false;
    }
    return true;
}

void RequestMessage::encode_header()
{
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", body_length_);
    std::memcpy(data_, header, header_length);
}