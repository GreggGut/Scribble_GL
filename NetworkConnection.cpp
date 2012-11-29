/*
 * File:   NetworkConnection.cpp
 * Author: scribble
 *
 * Created on November 25, 2012, 11:18 PM
 */

#include "NetworkConnection.h"

NetworkConnection::NetworkConnection(std::string address, std::string ip) : address(address), ip(ip)
{
    //try
    {
        //        boost::asio::io_service io_service;
        //
        //        tcp::resolver resolver(io_service);
        //
        //
        //
        //        tcp::resolver::query query(address, ip);
        //        tcp::resolver::iterator iterator = resolver.resolve(query);

        //
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(address, ip);
        iterator = resolver.resolve(query);

        //NetworkClient
        client = new NetworkClient(io_service, iterator);

        //boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
        thread_ = new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service));

        Sender s("greg");
        std::string toSend;
        //        toSend = s.Login("greg", "pass");
        //        c.write(sendMessage(toSend));

        toSend = s.GetFilesList();
        client->write(encodeMessage(toSend));

        toSend = s.RequestOwnership();
        client->write(encodeMessage(toSend));

        int pathID = 10;
        int page = 2;
        toSend = s.NewPath(pathID, true, 32453, true, page, 1);
        client->write(encodeMessage(toSend));

        Point m1(0, 0, 10, 10);
        Point m2(0, 0, 20, 20);
        Point m3(0, 0, 30, 30);
        Point m4(0, 0, 40, 40);

        std::vector<Point> mPoints;
        mPoints.push_back(m1);
        mPoints.push_back(m2);
        mPoints.push_back(m3);
        mPoints.push_back(m4);

        toSend = s.AddPoints(mPoints);
        client->write(encodeMessage(toSend));

        toSend = s.AddPoints(mPoints);
        client->write(encodeMessage(toSend));

        toSend = s.EndPath();
        client->write(encodeMessage(toSend));

        toSend = s.Undo(2);
        client->write(encodeMessage(toSend));

        toSend = s.GetFilesList();
        client->write(encodeMessage(toSend));

        toSend = s.DeletePath(page, pathID);
        client->write(encodeMessage(toSend));

        toSend = s.ReleaseOwnership();
        client->write(encodeMessage(toSend));

        //This is the sending function
        std::string line;

        //        while ( getline(std::cin, line) )
        //        {
        //            RequestMessage msg = encodeMessage(line);
        //            client->write(msg);
        //        }

        //        client->close();
        //        t.join();

        //        boost::asio::io_service io_service;
        //
        //        tcp::resolver resolver(io_service);
        //
        //
        //
        //        tcp::resolver::query query(address, ip);
        //        tcp::resolver::iterator iterator = resolver.resolve(query);
        //
        //        //NetworkClient
        //        client  = new NetworkClient(io_service, iterator);
        //        //client = client_;
        //
        //        boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
        //        //thread_ = boost::thread(boost::bind(&boost::asio::io_service::run, &io_service)); //= new boost::thread
        //
        //        Sender s("greg");
        //        std::string toSend;
        //        //        toSend = s.Login("greg", "pass");
        //        //        c.write(sendMessage(toSend));
        //
        //        toSend = s.GetFilesList();
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.RequestOwnership();
        //        client->write(encodeMessage(toSend));
        //
        //        int pathID = 10;
        //        int page = 2;
        //        toSend = s.NewPath(pathID, true, 32453, true, page, 1);
        //        client->write(encodeMessage(toSend));
        //
        //        Point m1(0, 0, 10, 10);
        //        Point m2(0, 0, 20, 20);
        //        Point m3(0, 0, 30, 30);
        //        Point m4(0, 0, 40, 40);
        //
        //        std::vector<Point> mPoints;
        //        mPoints.push_back(m1);
        //        mPoints.push_back(m2);
        //        mPoints.push_back(m3);
        //        mPoints.push_back(m4);
        //
        //        toSend = s.AddPoints(mPoints);
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.AddPoints(mPoints);
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.EndPath();
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.Undo(2);
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.GetFilesList();
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.DeletePath(page, pathID);
        //        client->write(encodeMessage(toSend));
        //
        //        toSend = s.ReleaseOwnership();
        //        client->write(encodeMessage(toSend));

        //This is the sending function
        //        std::string line;

        //        while ( getline(std::cin, line) )
        //        {
        //            RequestMessage msg = encodeMessage(line);
        //            client->write(msg);
        //        }

        std::cout << "Done with constructor..." << std::endl;

    }
    //    catch ( std::exception& e )
    //    {
    //        std::cerr << "Exception: " << e.what() << "\n";
    //    }
}

NetworkConnection::~NetworkConnection()
{
    std::cout << "Destructor called" << std::endl;
    //client.close();
    thread_->join();
}

RequestMessage NetworkConnection::encodeMessage(std::string line)
{
    //We need to add an end of line to the message
    line += '\n';
    RequestMessage msg;
    msg.body_length(std::strlen(line.c_str()));
    std::memcpy(msg.body(), line.c_str(), msg.body_length());
    msg.encode_header();

    return msg;

}

