/*
 * File:   defines.h
 * Author: greg
 *
 * Created on April 20, 2012, 9:43 AM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#define HEIGHT                  1024    //800
#define WIDTH                   768     //600
#define MENUWIDTH               102
#define PDF_RESOLUTION          90      //need to be adjusted
#define N_BUTTONS               9

#define SCREEN_UPDATE_TIMER     20
#define RESET_TIMER             300
#define REVIEW_TIMER            300
#define UPDATE_PATHS_VECTOR     2000
#define REVIEW_BUFFER           20

#define ERASEDELTA              5       //Used whenever erasing a path

#define CROP                    0xFF

//Error messages
#define CANNOT_OPEN_PORT        -2
#define CANNOT_OPEN_DOC         -3
#define CANNOT_ACCESS_PDF_PAGE  -4
#define PDF_TO_IMAGE_FAILED     -5

#define PATH                    "pdf/exam.pdf"
#define VERSION                 "Exam v0.8.2.4"

#define ANALYZE_BUFFER          5
#define MINIMUM_RADIUS          5       //To be0 adjusted
#define MAXIMUM_RADIUS          100//30      //To be adjusted but looks fine
#define MIN_R                   20
#define MINIMUM_PATH            60      //45

#define N_ROW                   7
#define N_COLUMN                10
#define IMAGE_PATH              "./resources/images/"
#define NETWORK 1
#define GL_FUCKUP 0

#endif	/* DEFINES_H */

