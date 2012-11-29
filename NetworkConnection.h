/*
 * File:   NetworkConnection.h
 * Author: scribble
 *
 * Created on November 25, 2012, 11:18 PM
 */

/*
 * NOT IN USE!!!!!!!!
 */

#ifndef NETWORKCONNECTION_H
#define	NETWORKCONNECTION_H

#include <cstdlib>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "RequestMessage.h"
#include "Sender.h"
#include "NetworkClient.h"

class NetworkConnection
{
public:
    NetworkConnection(std::string address, std::string ip);
    virtual ~NetworkConnection();

private:
    RequestMessage encodeMessage(std::string line);

private:
    std::string address;
    std::string ip;
    NetworkClient* client;
    boost::thread* thread_;

    //boost::asio::io_service io_service;

    //tcp::resolver resolver;
    //tcp::resolver::query query;
    tcp::resolver::iterator iterator;

};

#endif	/* NETWORKCONNECTION_H */

