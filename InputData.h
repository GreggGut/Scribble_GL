/*
 * File:   inputData.h
 * Author: greg
 *
 * Created on May 3, 2012, 10:43 AM
 */

#ifndef INPUTDATA_H
#define	INPUTDATA_H

#include "stdio.h"
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <pthread.h>
#include "Point.h"
#include <errno.h>   /* Error number definitions */
#include "defines.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <queue>
#include "ScribbleArea.h"
#include <stdlib.h>     /* Needed for the exit() function */

#include "PalmRejection.h"

using namespace std;

class InputData
{
public:
    InputData(ScribbleArea *);
    ~InputData();
    void run();
    void stop();

private:
    void initialise_port(int fd);
    int open_port();
    Point * read_data_from_file(int fd);
    ScribbleArea * scribbleAreaAccess;
    queue<Point* > *mPointsQueue;

    volatile bool stop_request;
    //int fd;

    //Should this be here or inside the read_data_from_file function?
    //Reasoning: read_data_from_file is called very often and this would reduce the recreation of those variable
    int column, row, uX, lX, uY, lY;
    
    PalmRejection palm;
};

#endif	/* INPUTDATA_H */