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
    void setPenColor(Color &newColor);
    void setPenWidth(int newWidth);
    bool pointInsideArea(Point * point);

    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent(/*Points *point*/);

    //void nextPage();
    //void previousPage();
    void undo();
    void redo();
    void write();
    void erase();
    void clearAll();

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

    Sender* getSender();
    /*
     * Used for networking Functions
     */

    std::vector<std::string> setFilesOnServer(std::vector<std::string> filesOnServer);
private:

    int x;
    int y;
    int width;
    int height;

    Color penColor;
    float penSize;

    int mMode;
    bool scribbling;

    std::vector<int> Paths_IDs;
    Path *mTempPath;

    Point lastPoint;

    boost::mutex pathsLock;
    boost::mutex lockForTempPath;

    int currentPage;
    std::vector< std::vector<Path*> > pathsOnPage;

    std::vector< std::vector<Path*> > redoVector;


    /*
     * Used for networking Variables
     */
    Sender* sender;
    boost::mutex lockForNetworkPath;
    int networkPathPage;
    Path* mNetworkPath;
    std::vector<std::string> filesOnServer;
};

#endif	/* SCRIBBLEAREA_H */

