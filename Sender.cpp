/*
 * File:   Sender.cpp
 * Author: scribble
 *
 * Created on October 30, 2012, 7:55 PM
 */

#include "Sender.h"

const std::string Sender::separator = "&";
const std::string Sender::separatorPoints = "#";

Sender::Sender(std::string username, NetworkClient* client) : username(username), client(client)
{
}

Sender::~Sender()
{
}

std::string Sender::getSeparator()
{
    return separator;
}

std::string Sender::getSeparatorPoints()
{
    return separatorPoints;
}

/**login - username - requestID++ - password
 *
 * @param username
 * @param password
 * @param myListeningPort
 */
void Sender::sendLogin(std::string password)
{
    //creating what needs to be send to the server for a login request
    std::string toSend = separator;
    toSend += NumberToString(LOGIN);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += password;
    //toSend += separator;

    client->sendMessage(toSend);
}

/** logout - username - requestID++
 *
 */
void Sender::sendLogout()
{
    //creating logout request
    std::string toSend = separator;
    toSend += NumberToString(LOGOUT);

    //toSend += separator;

    client->sendMessage(toSend);
}

/**
 * requestOwnership - username - requestID++
 */
void Sender::sendRequestOwnership()
{
    //creating Ownership request
    std::string toSend = separator;
    toSend += NumberToString(REQUEST_OWNERSHIP);

    toSend += separator;
    toSend += username;

    client->sendMessage(toSend);
}

/**
 * releaseOwnership - username - requestID++
 */
void Sender::sendReleaseOwnership()
{
    //creating Ownership release request
    std::string toSend = separator;
    toSend += NumberToString(RELEASE_OWNERSHIP);

    toSend += separator;
    toSend += username;

    client->sendMessage(toSend);
}

/**
 * getFileList - username - requestID++
 */
void Sender::sendGetFilesList()
{
    //creating get files list request
    std::string toSend = separator;
    toSend += NumberToString(GET_FILES_LIST);
    //toSend += separator;

    client->sendMessage(toSend);
}

/**TOCONFIRM Do we Need this?
 *
 * @param filename
 */
void Sender::sendDownloadFile(std::string filename)
{
    std::cout << "NOTHING DONE HERE.... in sendDownloadFile" << std::endl;
}

/** newPath - username - requestID++ - pathID - mode - color - active - page
 *
 * @param pathID
 * @param mode
 * @param color
 * @param active
 * @param page
 */
void Sender::sendNewPath(int pathID, bool mode, int color, bool active, int page, int width)
{
    //creating New Path request
    std::string toSend = separator;
    toSend += NumberToString(NEW_PATH);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    toSend += BoolToString(mode);
    toSend += separator;

    toSend += NumberToString(color);
    toSend += separator;

    toSend += BoolToString(active);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(width);
    //toSend += separator;

    client->sendMessage(toSend);
}

/** AddPoints - Points
 *
 * @param Points
 */
void Sender::sendPoints(Point* point)//std::vector<Point> points)
{
    //Creating the add points request
    std::string toSend = separator;
    toSend += NumberToString(ADD_POINTS);
    toSend += separator;

    toSend += GetPoints(point);

    client->sendMessage(toSend);
}

std::string Sender::GetPoints(Point* point)//std::vector<Point> points)
{
    std::stringstream s;
    //    for ( int i = 0; i < points.size(); i++ )
    //    {
    //        s << points.at(i).getX();
    //        s << separatorPoints;
    //        s << points.at(i).getY();
    //        s << separatorPoints;
    //    }

    s << point->getX();
    s << separatorPoints;
    s << point->getY();
    s << separatorPoints;

    std::string toReturn = s.str();
    toReturn.erase(toReturn.size() - 1);
    return toReturn;
}

/** EndPath
 *
 * @param pathID
 */
void Sender::sendEndPath()
{
    //Creating the end path request
    std::string toSend = separator;
    toSend += NumberToString(END_PATH);

    client->sendMessage(toSend);
}

/** Undo - page - pathID
 *
 * @param page
 * @param pathID
 */
void Sender::sendUndo(int page)
{
    std::string toSend = separator;
    toSend += NumberToString(UNDO);
    toSend += separator;

    toSend += NumberToString(page);
    //toSend += separator;

    client->sendMessage(toSend);
}

///** Redo - page - pathID
// *
// * @param page
// * @param pathID
// */
//std::string Sender::Redo(int page)
//{
//    std::string toSend = separator;
//    toSend += NumberToString(REDO);
//    toSend += separator;
//
//    toSend += NumberToString(page);
//
//    return toSend;
//}

/** Delete - page - pathID
 *
 * @param page
 * @param PathID
 */
void Sender::sendDeletePath(int page, int pathID)
{
    std::string toSend = separator;
    toSend += NumberToString(DELETE_PATH);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);
    //toSend += separator;

    client->sendMessage(toSend);
}

std::string Sender::NumberToString(int Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

std::string Sender::BoolToString(bool boolean)
{
    if ( boolean )
    {
        return "1";
    }
    return "0";
}