/*
 * File:   NetworkClient.h
 * Author: scribble
 *
 * Created on November 24, 2012, 3:51 PM
 */

#ifndef NETWORKCLIENT_H
#define	NETWORKCLIENT_H

#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>   //Used for boost split function
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "RequestMessage.h"
#include "Path.h"
#include "ScribbleArea.h"
#include <fstream>

using boost::asio::ip::tcp;

typedef std::deque<RequestMessage> chat_message_queue;

class NetworkClient
{
public:

    NetworkClient(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, ScribbleArea* scribbleArea);

    void close();
    void sendMessage(std::string line);

    tcp::socket& getSocket();
    ScribbleArea* getScribbleArea();
    bool isConnected();
    bool failedConnecting();
    void connect(tcp::resolver::iterator endpoint_iterator);

private:
    void write(const RequestMessage& msg);
    void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator);
    void handle_read_header(const boost::system::error_code& error);
    void handle_read_body(const boost::system::error_code& error);
    void do_write(RequestMessage msg);
    void handle_write(const boost::system::error_code& error);
    void do_close();
    void decodeRequest(std::string msg);

    void ServerConnectionFailed();

    RequestMessage encodeMessage(std::string line);

private:
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    RequestMessage read_msg_;
    chat_message_queue write_msgs_;
    ScribbleArea* scribbleArea;
    bool connected;
    bool connectionFailed;
    boost::asio::deadline_timer timer_;
};


#endif	/* NETWORKCLIENT_H */

