/* 
 * File:   Receiver.h
 * Author: scribble
 *
 * Created on November 10, 2012, 10:25 PM
 */

#ifndef RECEIVER_H
#define	RECEIVER_H

#include <vector>
#include <string>
#include <stdio.h>                      /* Standard input/output definitions */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <boost/thread.hpp>     //Used for boost thread
#include <boost/algorithm/string.hpp>   //Used for boost split function
#include <boost/thread/mutex.hpp>

#include "Sender.h"
#include "Color.h"
#include "Point.h"

#include "Request.h"
#include "NewPathRequest.h"
#include "AddPointsToPathRequest.h"
#include "EndCurrentPathRequest.h"
#include "UndoRequest.h"
#include "RedoRequest.h"
#include "DeletePathRequest.h"
#include "LogoutRequest.h"
#include "OwnershipRequest.h"
#include "FileListAvailableRequest.h"
#include "LoginRequest.h"

class Receiver
{
    typedef std::vector <Request*> Vector_Request;
public:
    Receiver(Vector_Request* mRequests, boost::mutex * requestsMutex, std::string username); // mRequests);
    virtual ~Receiver();

    int GetMListeningPort() const
    {
        return mListeningPort;
    }

private:

    void InitializeNetwork();
    std::string ToBytesConv(int integer);

    void ReceiverFunction();
    void AnalyzeThread(std::string * toAnalyze);

    boost::thread * workerThread;

    Sender* mySender;
    int mListeningPort;
    int sockfd;
    int newsockfd;
    //bool loggedIn;
    bool hasOwnership;
    int nextRequestID;

    //typedef std::vector <Request*> Vector_Request;
    Vector_Request *mRequests;

    boost::mutex* requestsMutex;

    std::string username;
    //std::string userFileOwner;

    enum protocol
    {
        LOG_IN_SUCCESSFUL = 0,
        LOG_IN_FAILED_WRONG_PASSWORD = 1,
        LOG_OUT_SUCCESSFUL = 2,
        LOG_OUT_FAILED = 3,
        ALLOW_OWNERSHIP = 4,
        DISALLOW_OWNERSHIP = 5,
        NEW_PATH = 6,
        ADD_POINTS_TO_PATH = 7,
        END_CURRENT_PATH = 8,
        UNDO_LAST_ACTION = 9,
        REDO_LAST_ACTION = 10,
        DELETE_PATH = 11,
        FILE_LIST_AVAILABLE = 12,
        PERIODIC_ALIVE_CHECK = 13,
        OWNERSHIP_IS_AVAILABLE = 14,
        LOG_IN_FAIL_USER_ALREADY_LOGGED_IN = 15
    };
};

#endif	/* RECEIVER_H */

