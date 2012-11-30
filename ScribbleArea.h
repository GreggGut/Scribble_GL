/*
 * File:   ScribbleArea.h
 * Author: scribble
 *
 * Created on October 25, 2012, 2:17 PM
 */

#ifndef SCRIBBLEAREA_H
#define	SCRIBBLEAREA_H

#include <GL/glu.h>
#include "Color.h"
#include "Path.h"
#include "Point.h"
#include <boost/thread/mutex.hpp>

class ScribbleArea
{
public:
    ScribbleArea();
    ScribbleArea(int x, int y, int w, int h);
    ScribbleArea(const ScribbleArea& orig);
    virtual ~ScribbleArea();
    void Draw();

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
    std::vector<std::vector<Path*> > getPathsOnPage();
    int getCurrentPage();
    void setLockForPath(bool lock);
    Path* getTempPath();

    void setNetworkPage(int p);
    void setNetworkPath(Path* p);
    void addNetworkPoint(Point * p);

private:

    void cleanRedoVector();
    void cleanPathsOnCurentPageVector();

    enum modes
    {
        WRITE, ERASE, MENU_PRESS, LOAD, SAVE_AS, COLOUR, SIZE_WRITE, SIZE_ERASE
    };

    enum
    {
        MENU_BUTTON_H = 40,
        MENU_BUTTON_W = 47,
        MENU_BUTTON_SPACING = 17
    };

    int xPos;
    int yPos;
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
    std::vector<std::vector<Path*> > pathsOnPage;
    std::vector< std::vector<Path*> > redoVector;

    //Used for networking
    boost::mutex lockForNetworkPath;
    int networkPathPage;
    Path* mNetworkPath;

};

#endif	/* SCRIBBLEAREA_H */

