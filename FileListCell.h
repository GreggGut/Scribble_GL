/* 
 * File:   FileListCell.h
 * Author: scribble
 *
 * Created on February 23, 2013, 8:25 PM
 */

#ifndef FILELISTCELL_H
#define	FILELISTCELL_H

#include "Button.h"

#define SELECTED_CELL_C 100

class FileListCell:public Button {
public:
    FileListCell();    
    FileListCell(int x_, int y_, int w_, int h_, int mode_, int action_, Color* fill_, Color* stroke_, Color* highlight_, Color* highlightStroke_, std::string fileName_, uint id_);
    FileListCell(const FileListCell& orig);
    virtual ~FileListCell();
    std::string getImagePath();
    std::string getFileName();
    uint getID();
private:
    std::string imagePath;
    std::string fileName;
    uint id;
};
#endif	/* FILELISTCELL_H */

