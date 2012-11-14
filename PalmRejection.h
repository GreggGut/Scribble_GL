/* 
 * File:   PalmRejection.h
 * Author: greg
 *
 * Created on May 23, 2012, 12:39 PM
 */

#ifndef PALMREJECTION_H
#define	PALMREJECTION_H

#include "Point.h"
//#include "QThread"
#include <pthread.h>
#include <iostream>
#include <vector>
#include "ScribbleArea.h"
#include <queue>
#include "ScreenAreas.h"
//#include <QWidget>
//#include "QTimer"
///////////////////////////

class PalmRejection
{
public:
    PalmRejection(ScribbleArea* scribble);
    virtual ~PalmRejection();
    void eventTouch(std::queue<Point* > *mPointsQueue);
    void eventMove(std::queue<Point* > *mPointsQueue);
    void eventRelease(/*Points *point*/);

private:
    void resetPalm();
    int mod(int, const int x = ANALYZE_BUFFER);
    int abs(int);
    float sqrt(int x);

    void analyzeNewSetOfPoints(); //this is done to reject possible "duplicates" of points caused on area edges
    void findPen_old(); //Find the pen, not necessarily there
    void findPen();
    void findNextPoint();
    void updatePalmMatrix(ushort slot, ushort ignore = -1);
    void updatePosition();
    void flushPointBuffer();
    bool firstTryFindingPenAndPalm();
    void compact_pointToAnalyze();

    float getDistance(int, int);

    ScribbleArea* scribble;
    bool stopRequest;
    ushort position;

    std::vector <std::vector < Point *> > pointToAnalyze;
    std::vector <Point *> possiblePenPoints;
    ushort sampling;
    bool penPresent;

    ScreenAreas mPalm;
    ScreenAreas mPen;

    //boost::asio::deadline_timer palmResetTimer;
    //boost::asio::io_service io;

    //used as reference points
    int mX;
    int mY;
};

#endif	/* PALMREJECTION_H */

