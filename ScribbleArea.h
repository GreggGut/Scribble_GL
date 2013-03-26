/*
 * File:   ScribbleArea.h
 * Author: scribble
 *
 * Created on October 25, 2012, 2:17 PM
 */
class Sender;


#ifndef SCRIBBLEAREA_H
#define	SCRIBBLEAREA_H

#include <GL/glu.h>
#include "Color.h"
#include "Path.h"
#include "Point.h"
#include <boost/thread/mutex.hpp>
#include "Document.h"

#define WRITE 0
#define ERASE 1

class ScribbleArea
{
public:
    ScribbleArea();
    ScribbleArea(int x_, int y_, int w_, int h_);
    ScribbleArea(const ScribbleArea& orig);
    virtual ~ScribbleArea();

    Color getPenColor();
    float getPenSize();
    void setPenColor(Color newColor);
    void setPenWidth(int newWidth);
    bool pointInsideArea(Point * point);

    void enableScribbleArea(bool en);
    bool getEnabled();

    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent(/*Points *point*/);

    //void nextPage();
    //void previousPage();
    void undo(int page);
    void redo(int page);
    void write();
    void erase();
    void clearAll(int page);

    int getMode();
    void setMode(int mode);
    std::vector<std::vector<Path*> > getPathsOnPage();
    int getCurrentPage();
    void setLockForTempPath(bool lock);
    void setLockForNetworkPath(bool lock);
    void setLockForPath(bool lock);
    Path* getTempPath();
    bool getScribbling();
    Path* getNetworkPath();
    int getNetworkPage();

    void setNetworkPage(int p);
    void setNetworkPath(Path* p);
    void addNetworkPoint(Point * p);
    void endNetworkPath();
    void setSender(Sender* sender);
    Document* getDocument();
    Sender* getSender();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void previousPage();
    void nextPage();
    void loadFile(std::string fileName);

    void setOwnershipMe();
    void setOwnershipFree();
    void setOwnershipTaken();
    /*
     * Used for networking Functions
     */
    void setFilesOnServer(std::vector<std::string> filesOnServer);
    void addFileOnServer(std::string file);
    void clearFilesOnServer();
    std::vector<std::string> getFilesOnServer();

    enum class NetworkActivity
    {
        NONE, WAITING_FOR_FILE_LIST, FILES_LIST_AVAILABLE, WAITING_FOR_FILE_DOWNLOAD, DOWNLOAD_COMPLETED, LOGIN_OK, LOGIN_FAILED,
        WAITING_LOGIN, FILE_DOWNLOAD_FAILED, LOST_NETWORK_CONNECTION, WAITING_FOR_NEW_FILE, NEW_FILE_ALREADY_EXISTS, NEW_FILE_CREATION_FAILED,
    };

    void setNetworkActivity(NetworkActivity n);
    NetworkActivity getNetworkActivity();

    int getOwnershipValue();

    enum Ownership
    {
        ME, TAKEN, FREE
    };

private:

    bool enable;
    bool network;

    int x;
    int y;
    int width;
    int height;

    Color penColor;
    float penSize;

    int mMode;
    bool scribbling;


    Path *mTempPath;
    Point lastPoint;

    boost::mutex pathsLock;
    boost::mutex lockForTempPath;

    std::vector<int> Paths_IDs;

    std::vector< std::vector<Path*> > pathsOnPage;
    std::vector< std::vector<Path*> > redoVector;

    Document *document;

    /*
     * Used for networking Variables
     */
    Sender* sender;
    boost::mutex lockForNetworkPath;
    int networkPathPage;
    Path* mNetworkPath;
    std::vector<std::string> filesOnServer;

    Ownership ownership;

    NetworkActivity networkActivity;
};

#endif	/* SCRIBBLEAREA_H */

