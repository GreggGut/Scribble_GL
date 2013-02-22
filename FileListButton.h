/* 
 * File:   FileListButton.h
 * Author: scribble
 *
 * Created on February 21, 2013, 8:15 PM
 */

#ifndef FILELISTBUTTON_H
#define	FILELISTBUTTON_H

#include "Button.h"

#define NEW_DOCUMENT_FL 0
#define NEXT_PAGE_FL 1
#define PREVIOUS_PAGE_FL 2

class FileListButton:public Button {
public:
    FileListButton();    
    FileListButton(int x_, int y_, int w_, int h_, int mode_, int action_, Color* fill_, Color* stroke_, Color* highlight_, Color* highlightStroke_,std::string image_);
    FileListButton(const FileListButton& orig);
    virtual ~FileListButton();
    std::string getImagePath();
    
private:
    std::string imagePath;
};

#endif	/* FILELISTBUTTON_H */

