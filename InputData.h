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
//#include "defines.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <queue>
#include "ScreenInterpreter.h"
#include <stdlib.h>     /* Needed for the exit() function */

#include "PalmRejection.h"

using namespace std;

class InputData
{
public:
    InputData(ScreenInterpreter *);
    ~InputData();
    void run();
    void stop();
    void endReader();
    void getData();
    void openScreen();
    
private:
    void initialise_port(int fd);
    int open_port();
    Point * read_data_from_file(int fd);
    ScreenInterpreter * scribbleAreaAccess;
    queue<Point* > *mPointsQueue;
    int fd;

    volatile bool stop_request;
    //int fd;

    //Should this be here or inside the read_data_from_file function?
    //Reasoning: read_data_from_file is called very often and this would reduce the recreation of those variable
    int column, row, uX, lX, uY, lY;
    
    PalmRejection palm;
    
    bool event;
    int number_of_points;
    int char_from_serial;

    int start_bit_1;
    int start_bit_2;
    
};

#endif	/* INPUTDATA_H */