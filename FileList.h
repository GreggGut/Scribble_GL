/* 
 * File:   FileList.h
 * Author: scribble
 *
 * Created on February 11, 2013, 4:07 AM
 */

#ifndef FILELIST_H
#define	FILELIST_H

#include <string>
#include "FileListButton.h"
#include <vector>
#include "defines.h"

class ScreenInterpreter;

class FileList {
public:
    FileList();
    FileList(int x_, int y_, int w_, int h_);
    FileList(const FileList& orig);
    virtual ~FileList();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    std::string getImagePath();
    void screenPressEvent(Point* point);
    void screenMoveEvent(Point* point);
    void screenReleaseEvent();
    void callAction(int action);
    void setScreenInterpreter(ScreenInterpreter *s);
    std::vector <FileListButton *> * getButtonArray();

        
private:
    int x;
    int y;
    int width;
    int height;
    std::string imagePath;
    std::vector<FileListButton *> *buttonArray;
    ScreenInterpreter *screenInterpreter;
};

#endif	/* FILELIST_H */

