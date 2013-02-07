/*
 * File:   NetworkClient.cpp
 * Author: scribble
 *
 * Created on November 24, 2012, 3:51 PM
 *
 * Parts of this code has been taken from boost.org under the Boost Software License Version 1.0:
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "NetworkClient.h"
#include "Sender.h"

NetworkClient::NetworkClient(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, ScribbleArea* scribbleArea) : io_service_(io_service),
socket_(io_service), scribbleArea(scribbleArea)
{
    tcp::endpoint endpoint = *endpoint_iterator;
    socket_.async_connect(endpoint, boost::bind(&NetworkClient::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
}

void NetworkClient::write(const RequestMessage& msg)
{
    //RequestMessage encodeMessage(std::string line)
    io_service_.post(boost::bind(&NetworkClient::do_write, this, msg));
}

void NetworkClient::close()
{
    io_service_.post(boost::bind(&NetworkClient::do_close, this));
}

void NetworkClient::handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator)
{
    if ( !error )
    {
        connected = true;
        boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), RequestMessage::header_length), boost::bind(&NetworkClient::handle_read_header, this, boost::asio::placeholders::error));
    }
    else if ( endpoint_iterator != tcp::resolver::iterator() )
    {
        connected = false;
        std::cout << "Fail connecting to server... Try again later" << std::endl;
        socket_.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        socket_.async_connect(endpoint, boost::bind(&NetworkClient::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
    }
}

void NetworkClient::handle_read_header(const boost::system::error_code& error)
{
    if ( !error && read_msg_.decode_header() )
    {
        boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), boost::bind(&NetworkClient::handle_read_body, this, boost::asio::placeholders::error));
    }
    else
    {
        do_close();
    }
}

void NetworkClient::handle_read_body(const boost::system::error_code& error)
{
    if ( !error )
    {
        //std::cout.write(read_msg_.body(), read_msg_.body_length());
        std::string msg(read_msg_.body(), read_msg_.body_length());
        decodeRequest(msg);
        boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), RequestMessage::header_length), boost::bind(&NetworkClient::handle_read_header, this, boost::asio::placeholders::error));
    }
    else
    {
        do_close();
    }
}

void NetworkClient::do_write(RequestMessage msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if ( !write_in_progress )
    {
        boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&NetworkClient::handle_write, this, boost::asio::placeholders::error));
    }
}

void NetworkClient::handle_write(const boost::system::error_code& error)
{
    if ( !error )
    {
        write_msgs_.pop_front();
        if ( !write_msgs_.empty() )
        {
            boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&NetworkClient::handle_write, this, boost::asio::placeholders::error));
        }
    }
    else
    {
        do_close();
    }
}

tcp::socket& NetworkClient::getSocket()
{
    return socket_;
}

void NetworkClient::do_close()
{
    std::cout << "Socket closed" << std::endl;
    socket_.close();
}

void NetworkClient::decodeRequest(std::string msg)
{
    //Removing the leading & and the lagging \n
    std::string received(msg, 1, msg.size() - 2);

    //Separating the received message
    std::vector<std::string> info;
    boost::split(info, received, boost::is_any_of(Sender::separator));
    int choice = atoi(info[0].c_str());
    std::cout << "Choice: " << choice << std::endl;
    switch ( choice )
    {
        case Sender::REQUEST_OWNERSHIP:
        {
            //We have received a message with who is the current owner
            std::cout << "REQUEST_OWNERSHIP" << std::endl;
            if ( info.size() > 1 && info[1] == scribbleArea->getSender()->getUsername() )
            {
                std::cout << "I got ownership" << std::endl;
                scribbleArea->setOwnershipMe();
            }
            else
            {
                std::cout << "I didn't get the ownership" << std::endl;
                scribbleArea->setOwnershipTaken();
            }
            break;
        }
        case Sender::RELEASE_OWNERSHIP:
        {
            //File ownership is available
            std::cout << "RELEASE_OWNERSHIP" << std::endl;
            scribbleArea->setOwnershipFree();
            break;
        }
        case Sender::NEW_PATH:
        {
            //Create new path
            std::cout << "NEW_PATH" << std::endl;
            int pathID = atoi(info[1].c_str());
            bool mode = ( info[2] == "1" ) ? true : false;
            int colorInt = atoi(info[3].c_str());
            //bool active = (info[4] == "1") ? true : false;
            int page = atoi(info[4].c_str());
            int width = atoi(info[5].c_str());

            int colorR = ( ( colorInt >> 16 ) & 0xFF );
            int colorG = ( ( colorInt >> 8 ) & 0xFF );
            int colorB = ( ( colorInt ) & 0xFF );

            Color color(colorR, colorG, colorB);
            Path* path = new Path(mode, color, width, pathID);

            scribbleArea->setNetworkPage(page);
            scribbleArea->setNetworkPath(path);

            break;
        }
        case Sender::ADD_POINTS:
        {
            //Add points to the current path
            std::cout << "ADD_POINTS" << std::endl;
            std::vector<std::string> p;
            boost::split(p, info[1], boost::is_any_of(Sender::separatorPoints));

            for ( int i = 0; i < p.size(); )
            {
                int x = atoi(p[i++].c_str());
                int y = atoi(p[i++].c_str());

                Point* point = new Point(x, y);
                scribbleArea->addNetworkPoint(point);
            }
            break;
        }
        case Sender::END_PATH:
        {
            //End current network path
            std::cout << "END_PATH" << std::endl;
            scribbleArea->endNetworkPath();
            break;
        }
        case Sender::UNDO:
        {
            //Undo last action, this will simply call the UNDO function of the ScribbleArea
            std::cout << "UNDO" << std::endl;
            scribbleArea->undo();
            break;
        }
        case Sender::REDO:
        {
            std::cout << "REDO" << std::endl;
            scribbleArea->redo();
            break;
        }
        case Sender::DELETE_PATH:
        {
            //Delete path, this will find the path to be deleted and completely remove it from the drawings
            std::cout << "DELETE_PATH" << std::endl;
            //TODO After integration with ScribbleArea find the path on page and delete it
            // alorithm:
            /*
             for(all paths on page)
                if(pathID=thisPathID)
                        remove
                        break
             */
            //TODO call the delete function of the scribble area...
            break;
        }
        case Sender::LOGIN:
        {
            //TOCONF NEED to link this with scribble area in order to let the user know login was fine or failed
            if ( info.size() > 1 && info[1] == "1" )
            {
                std::cout << "LOGIN FINE!!!!!! NEED TO SET some flag" << std::endl;
            }
            else
            {
                std::cout << "LOGIN FAILED!!!!!! NEED TO DISPLAY AN ERROR MESSAGE" << std::endl;
            }
            break;
        }
        case Sender::LOGOUT:
        {
            //TOCONF not in use for now
            std::cout << "LOGOUT" << std::endl;
            break;
        }
        case Sender::GET_FILES_LIST:
        {
            //We receive the list of all files available on the server
            std::cout << "GET_FILES_LIST" << std::endl;

            std::vector<std::string> files;
            boost::split(files, info[1], boost::is_any_of(Sender::separatorPoints));

            //REMOVE This needs to be removed once testing is completed
            std::cout << "Number of files: " << files.size() << std::endl;
            for ( int i = 0; i < files.size(); i++ )
            {
                std::cout << files[i] << std::endl;
            }
            scribbleArea->setFilesOnServer(files);
            break;
        }
        case Sender::DOWNLOAD_FILE:
        {
            //TOCONF will we use this??? possible use is to let the server know what file we are working on
            std::cout << "DOWNLOAD_FILE Got part of the message" << std::endl;
            break;
        }
        case Sender::CLEAR_ALL:
        {
            scribbleArea->clearAll();
            break;
        }
        case Sender::DOWNLOAD_FILE_DONE:
        {
            std::cout << "DOWNLOAD_FILE COMPLETED" << std::endl;
            break;
        }
        default:
            std::cout << "Should not be here" << std::endl;

    }
}

void NetworkClient::sendMessage(std::string line)
{
    //We need to add an end of line to the message
    line += '\n';
    RequestMessage msg;
    msg.body_length(std::strlen(line.c_str()));
    std::memcpy(msg.body(), line.c_str(), msg.body_length());
    msg.encode_header();

    write(msg);
}

ScribbleArea* NetworkClient::getScribbleArea()
{
    return scribbleArea;
}

bool NetworkClient::isConnected()
{
    return connected;
}