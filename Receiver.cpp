/* 
 * File:   Receiver.cpp
 * Author: scribble
 * 
 * Created on November 10, 2012, 10:25 PM
 */

#include "Receiver.h"


Receiver::Receiver(Vector_Request* requests, boost::mutex * requestsMutex, std::string username) : mRequests(requests), requestsMutex(requestsMutex), username(username)
{
    //requestsMutex = new boost::mutex();
    InitializeNetwork();
}

Receiver::~Receiver()
{
    ::close(newsockfd);
    ::close(sockfd);
}

void Receiver::InitializeNetwork()
{
    workerThread = new boost::thread(&Receiver::ReceiverFunction, this);

    //randomly assigned listening port within the acceptable range
    mListeningPort = rand() % ( 65535 - 49152 ) + 49152; //49152 through 65535

    std::cout << "My listening port: " << mListeningPort << std::endl;

    //    //TODO server address and port should be variables that the user can change if needed
    //    std::string add = "127.0.0.1";
    //    mySender = new Sender(add, 21223);
    //    mySender->Login(username, password, mListeningPort);
    //The test do not have to be started as a thread, but this was a test and it stayed this way
    //boost::thread(&Receiver::SendTests, this);

    nextRequestID = 0;
}

void Receiver::ReceiverFunction()
{
    std::cout << "Been in ReceiverFunction" << std::endl;


    socklen_t clilen;
    char buffer[256];
    //std::string receivedPacket;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockfd < 0 )
    {
        std::cout << "ERROR opening socket";
    }


    bzero(( char * ) &serv_addr, sizeof (serv_addr ));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(mListeningPort);

    if ( bind(sockfd, ( struct sockaddr * ) &serv_addr, sizeof (serv_addr )) < 0 )
    {
        std::cout << "ERROR on binding";
    }

    listen(sockfd, 5);
    clilen = sizeof (cli_addr );

    while ( 1 )
    {
        newsockfd = accept(sockfd, ( struct sockaddr * ) &cli_addr, &clilen);
        if ( newsockfd < 0 )
        {
            std::cout << "ERROR on accept";
        }
        bzero(buffer, 256);

        n = read(newsockfd, buffer, 255);
        if ( n < 0 )
        {
            std::cout << "ERROR reading from socket";
        }
        ::close(newsockfd);

        /**
         * Once we received something we start the AnalyzeThread in order to determine what has been received
         */
        boost::thread(&Receiver::AnalyzeThread, this, new std::string(buffer));

    }
    ::close(sockfd);
}

void Receiver::AnalyzeThread(std::string *toAnalyze)
{
    //TESTING
    std::cout << *toAnalyze << std::endl;

    //Separating the received message
    std::vector<std::string> info;
    boost::split(info, *toAnalyze, boost::is_any_of(Sender::getSeparator()));

//    std::cout << "Size is: " << info.size() << std::endl;
//    for ( uint i = 0; i < info.size(); i++ )
//    {
//        std::cout << info.at(i) << std::endl;
//    }

    int choice = atoi(info[0].c_str());

    switch ( choice )
    {
        case LOG_IN_SUCCESSFUL:
            //At this point user can use the network interface/capabilities of Scribble
            //loggedIn = true;
            //std::cout << "Login fine" << std::endl;
        {
            int reqID = atoi(info[1].c_str());
            LoginRequest* request = new LoginRequest(reqID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }
        case LOG_IN_FAILED_WRONG_PASSWORD:
            //TODO Error message, wrong username/password
            break;

        case LOG_OUT_SUCCESSFUL:
        {
            //User is logged out, cannot do anything else related to the network capabilities of Scribble
            int reqID = atoi(info[1].c_str());
            LogoutRequest* request = new LogoutRequest(reqID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();
            //loggedIn = false;
            break;
        }
        case LOG_OUT_FAILED:
            //TOCONF why would this happen???? Is this needed?
            break;

        case ALLOW_OWNERSHIP:
        {
            //Parsing what has been received
            std::string user = info[1].c_str();
            int reqID = atoi(info[2].c_str());
            int nextRequest = atoi(info[3].c_str());

            //Creating the request
            OwnershipRequest * request = new OwnershipRequest(reqID, user, nextRequest);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }

        case DISALLOW_OWNERSHIP:
            //TODO What can I do with this?
            //std::cout << "Someone else has ownership" << std::endl;
            break;

        case NEW_PATH:
        {
            //std::cout << "Been in new path" << std::endl;
            //newPath - username - requestID - pathID - mode - color - active - page

            //Converting received info to a new path
            int reqID = atoi(info[2].c_str());
            int pathID = atoi(info[3].c_str());
            bool mode = ( info[4].c_str() != "0" );
            int colorInt = atoi(info[5].c_str());

            int colorR = ( ( colorInt >> 16 ) & 0xFF );
            int colorG = ( ( colorInt >> 8 ) & 0xFF );
            int colorB = ( ( colorInt ) & 0xFF );

            Color color(colorR, colorG, colorB);

            bool active = ( info[6].c_str() != "0" );
            int page = atoi(info[7].c_str());
            int width = atoi(info[8].c_str());

            //Creating a new path request
            NewPathRequest* request = new NewPathRequest(reqID, pathID, mode, color, active, page, width);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();
            break;
        }

        case ADD_POINTS_TO_PATH:
        {
            //std::cout << "Been in add points to path" << std::endl;
            //AddPoints - username - requestID++ - pathID - numberOfPoints - Points

            //Converting received info to a new path
            int reqID = atoi(info[2].c_str());
            int pathID = atoi(info[3].c_str());
            int nPoints = atoi(info[4].c_str());
            std::string points = info[5];

            //Creating add points to path request
            AddPointsToPathRequest* request = new AddPointsToPathRequest(reqID, pathID, nPoints, points);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }
        case END_CURRENT_PATH:
        {
            //std::cout << "Been in end path" << std::endl;
            //EndPath - username - requestID - pathID

            //Converting received info to end current path
            int reqID = atoi(info[2].c_str());
            int pathID = atoi(info[3].c_str());

            //Creating end path request
            EndCurrentPathRequest * request = new EndCurrentPathRequest(reqID, pathID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }
        case UNDO_LAST_ACTION:
        {
            //Undo - username - requestID - page - pathID
            //std::cout << "Been in undo" << std::endl;

            int reqID = atoi(info[2].c_str());
            int page = atoi(info[3].c_str());
            int pathID = atoi(info[4].c_str());

            UndoRequest * request = new UndoRequest(reqID, page, pathID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();
            break;
        }
        case REDO_LAST_ACTION:
        {
            //Redo - username - requestID - page - pathID
            //std::cout << "Been in redo" << std::endl;

            int reqID = atoi(info[2].c_str());
            int page = atoi(info[3].c_str());
            int pathID = atoi(info[4].c_str());

            RedoRequest * request = new RedoRequest(reqID, page, pathID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();
            break;
        }
        case DELETE_PATH:
        {
            //Delete - username - requestID - page - pathID 
            //std::cout << "Been in delete path" << std::endl;

            int reqID = atoi(info[2].c_str());
            int page = atoi(info[3].c_str());
            int pathID = atoi(info[4].c_str());

            DeletePathRequest * request = new DeletePathRequest(reqID, page, pathID);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }
        case FILE_LIST_AVAILABLE:
        {
            //Parsing received info
            //TOCONF we might need to have a request ID for this, for now the constructor of this request sets the request ID as -1;
            int reqID = atoi(info[1].c_str());
            std::string files = info[2];

            //Creating the new request
            FileListAvailableRequest* request = new FileListAvailableRequest(reqID, files);

            //Adding the add new path request to the request list
            requestsMutex->lock();
            mRequests->push_back(request);
            requestsMutex->unlock();

            break;
        }
        case PERIODIC_ALIVE_CHECK:
        {
            //TODO send I am alive
            break;
        }
        case OWNERSHIP_IS_AVAILABLE:
        {

            break;
        }
        case LOG_IN_FAIL_USER_ALREADY_LOGGED_IN:
        {
            break;
        }
        default:
        {
            std::cout << "Decoding error occurred....." << std::endl;
            break;
        }

    }
}

/**
 * TOCONF this function is not used at the moment, might have to delete it
 * @param integer
 * @return 
 */
std::string Receiver::ToBytesConv(int integer)
{
    integer = 1100;
    unsigned char bytes[2];
    bytes[0] = ( integer >> 8 ) & 0xFF;
    bytes[1] = integer & 0xFF;
    std::cout << ( int ) bytes[0] << " " << ( int ) bytes[1] << std::endl;

    std::stringstream s;
    s << bytes[0];
    s << bytes[1];

    std::string toReturn = s.str();

    //    int backTogether = bytes[1];
    //    backTogether += bytes[0] << 8;
    //    std::cout << "together: " << backTogether << std::endl;

    return toReturn;
}