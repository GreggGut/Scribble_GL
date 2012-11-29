/*
 * File:   Sender.h
 * Author: scribble
 *
 * Created on October 30, 2012, 7:55 PM
 */

#ifndef SENDER_H
#define	SENDER_H

#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "Point.h"

class Sender
{
public:
    Sender(std::string username);
    //    Sender(const Sender& orig);
    virtual ~Sender();

    static std::string getSeparator();
    static std::string getSeparatorPoints();

    //login - username - requestID - password - port
    std::string Login( std::string password);

    //logout - username - requestID
    std::string Logout();

    //requestOwnership - username - requestID
    std::string RequestOwnership();

    //releaseOwnership - username - requestID
    std::string ReleaseOwnership();

    //getFileList - username - requestID
    std::string GetFilesList();

    //TOCONFIRM Do we Need this?
    std::string DownloadFile(std::string filename);

    //newPath - username - requestID - pathID - mode - color - active - page
    std::string NewPath(int pathID, bool mode, int color, bool active, int page, int width);

    //AddPoints - username - requestID - pathID - numberOfPoints - Points
    std::string AddPoints(std::vector<Point> points);

    //EndPath
    std::string EndPath();

    //Undo - page
    std::string Undo(int page);

    //Redo - username - requestID - page - pathID
    std::string Redo(int page, int pathID);

    //Delete - username - requestID - page - pathID
    std::string DeletePath(int page, int PathID);

public:

    static enum Protocol
    {
        //Client to server
        LOGIN = 0,
        LOGOUT = 1,
        REQUEST_OWNERSHIP = 2,
        RELEASE_OWNERSHIP = 3,
        GET_FILES_LIST = 4,
        DOWNLOAD_FILE = 5, //TOCONFIRM do we need this?
        NEW_PATH = 6,
        ADD_POINTS = 7,
        END_PATH = 8,
        UNDO = 9,
        REDO = 10,
        DELETE_PATH = 11,
    } protocol;

    static const std::string separator; // = "&";
    static const std::string separatorPoints; // = "#";

private:
    std::string GetPoints(std::vector<Point> points);

    std::string NumberToString(int Number);
    std::string BoolToString(bool boolean);

    std::string serverName;
    int portno;

    //Need to initialise this in login
    std::string username;



};

#endif	/* SENDER_H */