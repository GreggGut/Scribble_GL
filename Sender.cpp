/* 
 * File:   Sender.cpp
 * Author: scribble
 * 
 * Created on October 30, 2012, 7:55 PM
 */

#include "Sender.h"

const std::string Sender::separator = "&";
const std::string Sender::separatorPoints = "#";

Sender::Sender(std::string serverName, int port) : /*separator("&"), separatorPoints("#"),*/ portno(port), requestID(0)
{
    this->serverName = serverName;
}

Sender::~Sender()
{
}

void Sender::SendMessage(std::string toSend)
{

    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(serverName.c_str());
    if ( server == NULL )
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero(( char * ) &serv_addr, sizeof (serv_addr ));
    serv_addr.sin_family = AF_INET;
    bcopy(( char * ) server->h_addr,
            ( char * ) &serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);
    if ( connect(sockfd, ( struct sockaddr * ) &serv_addr, sizeof (serv_addr )) < 0 )
    {
        std::cout << "The server is unavailable, try again later" << std::endl;
        close(sockfd);
        return;
    }

    n = write(sockfd, toSend.c_str(), toSend.length());

    if ( n < 0 )
    {
        std::cout << "ERROR writing to socket" << std::endl;
    }
    close(sockfd);
}

std::string Sender::getSeparator()
{
    return separator;
}

std::string Sender::getSeparatorPoints()
{
    return separatorPoints;
}

/**login - username - requestID++ - password - port
 * 
 * @param username
 * @param password
 * @param myListeningPort
 */
void Sender::Login(std::string username, std::string password, int myListeningPort)
{
    //Saving username since it will be use with all requests
    this->username = username;

    //creating what needs to be send to the server for a login request
    std::string toSend = NumberToString(LOGIN);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += password;
    toSend += separator;

    toSend += NumberToString(myListeningPort);
    toSend += separator;

    //Sending login request
    SendMessage(toSend);
}

/** logout - username - requestID++
 * 
 */
void Sender::Logout()
{
    //creating logout request
    std::string toSend = NumberToString(LOGOUT);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    //Sending logout request
    SendMessage(toSend);
}

/**
 * requestOwnership - username - requestID++
 */
void Sender::RequestOwnership()
{
    //creating Ownership request
    std::string toSend = NumberToString(REQUEST_OWNERSHIP);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    //Sending logout request
    SendMessage(toSend);
}

/**
 * releaseOwnership - username - requestID++
 */
void Sender::ReleaseOwnership()
{
    //creating Ownership release request
    std::string toSend = NumberToString(RELEASE_OWNERSHIP);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    //Sending logout request
    SendMessage(toSend);
}

/**
 * getFileList - username - requestID++
 */
void Sender::GetFilesList()
{
    //creating get files list request
    std::string toSend = NumberToString(GET_FILES_LIST);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    //Sending logout request
    SendMessage(toSend);
}

/**TOCONFIRM Do we Need this?
 * 
 * @param filename
 */
void Sender::DownloadFile(std::string filename)
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
void Sender::NewPath(int pathID, bool mode, int color, bool active, int page)
{
    //creating New Path request
    std::string toSend = NumberToString(NEW_PATH);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
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

    //std::cout << "NewPath: " << toSend << std::endl;
    //Sending logout request
    SendMessage(toSend);
}

/** AddPoints - username - requestID++ - pathID - numberOfPoints - Points
 * 
 * @param pathID
 * @param numberOfPoints
 * @param Points
 */
void Sender::AddPoints(int pathID, int numberOfPoints, std::vector<Point> points)
{
    //Creating the add points request
    std::string toSend = NumberToString(ADD_POINTS);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    toSend += NumberToString(numberOfPoints);
    toSend += separator;

    toSend += GetPoints(points);
    toSend += separator;

    //Seding the Add Points request
    SendMessage(toSend);
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
    return s.str();
}

/** EndPath - username - requestID++ - pathID
 * 
 * @param pathID
 */
void Sender::EndPath(int pathID)
{
    //Creating the end path request
    std::string toSend = NumberToString(END_PATH);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    //Sending end path request
    SendMessage(toSend);
}

/** Undo - username - requestID++ - page - pathID
 * 
 * @param page
 * @param pathID
 */
void Sender::Undo(int page, int pathID)
{
    std::string toSend = NumberToString(UNDO);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    //Sending the Undo request
    SendMessage(toSend);
}

/** Redo - username - requestID++ - page - pathID
 * 
 * @param page
 * @param pathID
 */
void Sender::Redo(int page, int pathID)
{
    std::string toSend = NumberToString(REDO);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    //Sending the Redo request
    SendMessage(toSend);
}

/** Delete - username - requestID++ - page - pathID 
 * 
 * @param page
 * @param PathID
 */
void Sender::DeletePath(int page, int pathID)
{
    std::string toSend = NumberToString(DELETE_PATH);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += NumberToString(requestID++);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    //Sending the Delete path request
    SendMessage(toSend);
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