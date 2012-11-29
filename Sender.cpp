/*
 * File:   Sender.cpp
 * Author: scribble
 *
 * Created on October 30, 2012, 7:55 PM
 */

#include "Sender.h"

const std::string Sender::separator = "&";
const std::string Sender::separatorPoints = "#";

Sender::Sender(std::string username) : username(username)
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
std::string Sender::Login(std::string password)
{
    //creating what needs to be send to the server for a login request
    std::string toSend = separator;
    toSend += NumberToString(LOGIN);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += password;
    //toSend += separator;

    return toSend;
}

/** logout - username - requestID++
 *
 */
std::string Sender::Logout()
{
    //creating logout request
    std::string toSend = separator;
    toSend += NumberToString(LOGOUT);

    //toSend += separator;

    return toSend;
}

/**
 * requestOwnership - username - requestID++
 */
std::string Sender::RequestOwnership()
{
    //creating Ownership request
    std::string toSend = separator;
    toSend += NumberToString(REQUEST_OWNERSHIP);

    toSend += separator;
    toSend += username;

    return toSend;
}

/**
 * releaseOwnership - username - requestID++
 */
std::string Sender::ReleaseOwnership()
{
    //creating Ownership release request
    std::string toSend = separator;
    toSend += NumberToString(RELEASE_OWNERSHIP);

    toSend += separator;
    toSend += username;

    return toSend;
}

/**
 * getFileList - username - requestID++
 */
std::string Sender::GetFilesList()
{
    //creating get files list request
    std::string toSend = separator;
    toSend += NumberToString(GET_FILES_LIST);
    //toSend += separator;

    return toSend;
}

/**TOCONFIRM Do we Need this?
 *
 * @param filename
 */
std::string Sender::DownloadFile(std::string filename)
{

}

/** newPath - username - requestID++ - pathID - mode - color - active - page
 *
 * @param pathID
 * @param mode
 * @param color
 * @param active
 * @param page
 */
std::string Sender::NewPath(int pathID, bool mode, int color, bool active, int page, int width)
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

    return toSend;
}

/** AddPoints - Points
 *
 * @param Points
 */
std::string Sender::AddPoints(std::vector<Point> points)
{
    //Creating the add points request
    std::string toSend = separator;
    toSend += NumberToString(ADD_POINTS);
    toSend += separator;

    toSend += GetPoints(points);

    return toSend;
}

std::string Sender::GetPoints(std::vector<Point> points)
{
    std::stringstream s;
    for ( int i = 0; i < points.size(); i++ )
    {
        s << points.at(i).getX();
        s << separatorPoints;
        s << points.at(i).getY();
        s << separatorPoints;
    }
    std::string toReturn = s.str();
    toReturn.erase(toReturn.size()-1);
    return toReturn;
}

/** EndPath
 *
 * @param pathID
 */
std::string Sender::EndPath()
{
    //Creating the end path request
    std::string toSend = separator;
    toSend += NumberToString(END_PATH);

    return toSend;
}

/** Undo - page - pathID
 *
 * @param page
 * @param pathID
 */
std::string Sender::Undo(int page)
{
    std::string toSend = separator;
    toSend += NumberToString(UNDO);
    toSend += separator;

    toSend += NumberToString(page);
    //toSend += separator;

    return toSend;
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

/** Delete - username - requestID++ - page - pathID
 *
 * @param page
 * @param PathID
 */
std::string Sender::DeletePath(int page, int pathID)
{
    std::string toSend = separator;
    toSend += NumberToString(DELETE_PATH);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);
    //toSend += separator;

    return toSend;
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