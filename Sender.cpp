/*
 * File:   Sender.cpp
 * Author: scribble
 *
 * Created on October 30, 2012, 7:55 PM
 */

#include "Sender.h"

const std::string Sender::separator = "&";
const std::string Sender::separatorPoints = "#";

Sender::Sender(std::string username, NetworkClient* client, std::string serverName) : username(username), client(client), serverName(serverName)
{
}

Sender::~Sender()
{
}

/**
 * Get the separator between the info in a sent message
 *
 * @return Message separator
 */
std::string Sender::getSeparator()
{
    return separator;
}

/**
 * Get the separator used between points
 *
 * @return Point separator
 */
std::string Sender::getSeparatorPoints()
{
    return separatorPoints;
}

/**
 * Send login request
 *
 * @param password User password
 *
 * Info sent: login - username - password
 */
void Sender::sendLogin(std::string password)
{
    std::string toSend = separator;
    toSend += NumberToString(LOGIN);
    toSend += separator;

    toSend += username;
    toSend += separator;

    toSend += password;

    client->sendMessage(toSend);
}

/**
 * Send logout request
 *
 * Info sent: logout
 */
void Sender::sendLogout()
{
    std::string toSend = separator;
    toSend += NumberToString(LOGOUT);

    client->sendMessage(toSend);
}

/**
 * Send Ownership request
 *
 * Info sent: requestOwnership - username
 */
void Sender::sendRequestOwnership()
{
    std::string toSend = separator;
    toSend += NumberToString(REQUEST_OWNERSHIP);

    toSend += separator;
    toSend += username;

    client->sendMessage(toSend);
}

/**
 * Send Release ownership request
 *
 * Info sent: releaseOwnership - username
 */
void Sender::sendReleaseOwnership()
{
    std::string toSend = separator;
    toSend += NumberToString(RELEASE_OWNERSHIP);

    toSend += separator;
    toSend += username;

    client->sendMessage(toSend);
}

/**
 * Send Get file list request
 *
 * Info sent: GetFileList
 */
void Sender::sendGetFilesList()
{
    std::string toSend = separator;
    toSend += NumberToString(GET_FILES_LIST);

    client->sendMessage(toSend);
}

/**TOCONFIRM This needs to be fully tested
 *
 * @param filename
 */
void Sender::sendDownloadFile(std::string filename)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int LENGTH = 512;

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
    //TODO take the port number from the main
    //The port number is the regular port number +1
    serv_addr.sin_port = htons(21224); //portno);
    if ( connect(sockfd, ( struct sockaddr * ) &serv_addr, sizeof (serv_addr )) < 0 )
    {
        std::cout << "The server is unavailable, try again later" << std::endl;
        close(sockfd);
        return;
    }

    //Converting filename to bytes and sending name to server
    signed char filename2[filename.size()];

    filename2[filename.size()] = 0;
    memcpy(filename2, filename.c_str(), filename.size());
    write(sockfd, filename2, filename.size());


    signed char buffer[LENGTH];
    bzero(buffer, LENGTH);
    int fr_block_sz = 0;
    char* fr_name = ( char* ) filename.c_str();
    FILE *fr = fopen(fr_name, "w");
    while ( fr_block_sz = read(sockfd, buffer, LENGTH - 1) )
    {
        if ( fr_block_sz < 0 )
        {
            break;
        }
        int write_sz = fwrite(buffer, sizeof (char ), fr_block_sz, fr);
        if ( write_sz < fr_block_sz )
        {
            printf("File write failed.\n");
        }
        bzero(buffer, LENGTH);

    }
    printf("File received from server!\n");
    fclose(fr);
    close(sockfd);

    /*
     * Sending filename to server to let it know on which file I am working
     */
    std::string toSend = separator;
    toSend += NumberToString(DOWNLOAD_FILE);

    toSend += separator;
    toSend += filename;
    client->sendMessage(toSend);

    sendUpdateFileContent();
}

void Sender::sendUpdateFileContent()
{
    std::string toSend = separator;
    toSend += NumberToString(UPDATE_FILE_CONTENT);

    client->sendMessage(toSend);
}

/**
 * Send a new path request
 *
 * @param pathID Path ID
 * @param mode Path mode
 * @param color Path color
 * @param active Path state
 * @param page Page on which the path has been drawn
 * @param width Path width
 *
 * Info sent: newPath - pathID - mode - color - active - page - width
 */
void Sender::sendNewPath(int pathID, bool mode, int color/*, bool active*/, int page, int width)
{
    std::string toSend = separator;
    toSend += NumberToString(NEW_PATH);
    toSend += separator;

    toSend += NumberToString(pathID);
    toSend += separator;

    toSend += BoolToString(mode);
    toSend += separator;

    toSend += NumberToString(color);
    toSend += separator;
    
    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(width);

    client->sendMessage(toSend);
}

/**
 * Send a new point request
 * @param point
 *
 * Info sent: AddPoints - Points...
 */
void Sender::sendPoints(Point* point)//std::vector<Point> points)
{
    std::string toSend = separator;
    toSend += NumberToString(ADD_POINTS);
    toSend += separator;

    toSend += GetPoints(point);

    client->sendMessage(toSend);
}

/**
 * Transform a point to a string
 *
 * @param point The point to the transformed to a string
 * @return A string representing a point
 */
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

/** Send en End of Path request
 *
 * @param pathID
 *
 * Info sent: EndPath
 */
void Sender::sendEndPath()
{
    std::string toSend = separator;
    toSend += NumberToString(END_PATH);

    client->sendMessage(toSend);
}

/**
 * Send an undo request
 *
 * @param page
 * @param pathID
 *
 * Info sent: Undo - page - pathID
 */
void Sender::sendUndo(int page)
{
    std::string toSend = separator;
    toSend += NumberToString(UNDO);
    toSend += separator;

    toSend += NumberToString(page);

    client->sendMessage(toSend);
}

/** Redo - page - pathID
 *
 * @param page
 * @param pathID
 */
void Sender::sendRedo(int page)
{
    std::string toSend = separator;
    toSend += NumberToString(REDO);
    toSend += separator;

    toSend += NumberToString(page);

    client->sendMessage(toSend);
}

/**
 * Send a delete Path request
 * @param page
 * @param PathID
 *
 * Info sent: Delete - page - pathID
 */
void Sender::sendDeletePath(int page, int pathID)
{
    std::string toSend = separator;
    toSend += NumberToString(DELETE_PATH);
    toSend += separator;

    toSend += NumberToString(page);
    toSend += separator;

    toSend += NumberToString(pathID);

    client->sendMessage(toSend);
}

void Sender::sendCleanAll(int page)
{
    std::string toSend = separator;
    toSend += NumberToString(CLEAR_ALL);
    toSend += separator;

    toSend += NumberToString(page);

    client->sendMessage(toSend);
}

/**
 * Number to String
 * @param Number What we want to transform to string
 * @return A string corresponding to the input number
 */
std::string Sender::NumberToString(int Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

/**
 * Converting from boolean to a string
 * @param boolean
 * @return 1 if true, 0 if false
 */
std::string Sender::BoolToString(bool boolean)
{
    if ( boolean )
    {
        return "1";
    }
    return "0";
}