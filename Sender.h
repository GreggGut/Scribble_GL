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
#include "NetworkClient.h"

#include <cassert>
#include <fstream>
#include <arpa/inet.h>

class Sender {
public:
    Sender(std::string username, NetworkClient* client);
    //    Sender(const Sender& orig);
    virtual ~Sender();

    static std::string getSeparator();
    static std::string getSeparatorPoints();

    //login - username - requestID - password - port
    void sendLogin(std::string password);

    //logout - username - requestID
    void sendLogout();

    //requestOwnership - username - requestID
    void sendRequestOwnership();

    //releaseOwnership - username - requestID
    void sendReleaseOwnership();

    //getFileList - username - requestID
    void sendGetFilesList();

    //TOCONFIRM Do we Need this?
    void sendDownloadFile(std::string filename);

    void sendUpdateFileContent();

    //newPath - username - requestID - pathID - mode - color - active - page
    void sendNewPath(int pathID, bool mode, int color/*, bool active*/, int page, int width);

    //AddPoints - username - requestID - pathID - numberOfPoints - Points
    void sendPoints(Point* point); //std::vector<Point> points);

    //EndPath
    void sendEndPath();

    //Undo - page
    void sendUndo(int page);

    //Redo - page
    void sendRedo(int page);//, int pathID);

    //Delete - username - requestID - page - pathID
    void sendDeletePath(int page, int PathID);

    void sendCleanAll(int page);

public:

    static enum Protocol {
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
        CLEAR_ALL = 12,
        UPDATE_FILE_CONTENT = 13,
    } protocol;

    static const std::string separator; // = "&";
    static const std::string separatorPoints; // = "#";

private:

//    int getPenColorInt(Color c);
    std::string GetPoints(Point* point); //std::vector<Point> points);

    std::string NumberToString(int Number);
    std::string BoolToString(bool boolean);

    std::string serverName;
    int portno;

    //Need to initialise this in login
    std::string username;
    NetworkClient* client;



};

#endif	/* SENDER_H */