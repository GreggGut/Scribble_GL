/* 
 * File:   FileList.cpp
 * Author: scribble
 * 
 * Created on February 11, 2013, 4:07 AM
 */

#include "FileList.h"
#include "ScreenInterpreter.h"
#include "Sender.h"

FileList::FileList() {
}

FileList::FileList(const FileList& orig) {
}

FileList::~FileList() {

    for (uint i = 0; i < buttonArray->size(); i++) {
        delete buttonArray->at(i);
    }

    buttonArray->clear();

    delete buttonArray;

    for (uint i = 0; i < fileTable->size(); i++) {
        delete fileTable->at(i);
    }

    fileTable->clear();

    delete fileTable;
}

FileList::FileList(int x_, int y_, int w_, int h_) {

    start = 0;
    size = 0;
    numberOfPages = 0;
    page = 0;

    x = x_;
    y = y_;
    width = w_;
    height = h_;

    std::string fileName = "FileListBG.png";
    imagePath = fileName.insert(0, IMAGE_PATH);

    buttonArray = new std::vector<FileListButton *>;
    fileTable = new std::vector<FileListCell *>;

    for (int i = 0; i < 3; ++i) {

        int type;
        int action;
        int btnx;
        int btny;
        int btnw;
        int btnh;
        std::string buttonImage;

        switch (i) {
            case 0:
                type = MOMENTARY;
                action = NEW_DOCUMENT_FL;
                buttonImage = "AddDocument.png";
                btnx = 604;
                btny = 9;
                btnw = 40;
                btnh = 40;
                break;
            case 1:
                type = MOMENTARY;
                action = NEXT_PAGE_FL;
                buttonImage = "NextPage.png";
                btnx = 604;
                btny = 688;
                btnw = 40;
                btnh = 40;
                break;
            case 2:
                type = MOMENTARY;
                action = PREVIOUS_PAGE_FL;
                buttonImage = "PreviousPage.png";
                btnx = 559;
                btny = 688;
                btnw = 40;
                btnh = 40;
                break;
            default:
                type = MOMENTARY;
                action = NULL;
                buttonImage = "";
                btnx = 0;
                btny = 0;
                btnw = 0;
                btnh = 0;
                break;
        }


        FileListButton *btn = new FileListButton(btnx + x, btny + y, btnw, btnh, type, action, NULL, NULL, NULL, NULL, buttonImage.insert(0, IMAGE_PATH));
        buttonArray->push_back(btn);

    }
}

int FileList::getX() {
    return x;
}

int FileList::getY() {
    return y;
}

int FileList::getWidth() {
    return width;
}

int FileList::getHeight() {
    return height;
}

std::string FileList::getImagePath() {
    return imagePath;
}

/*! Screen Press Event
 *
 * \param *point A pointer to a Point object
 *
 * This function initializes the lastPoint and enables scribbling in Write mode, or tries to delete a path on which the point passes through in Erase mode
 */
void FileList::screenPressEvent(Point* point) {
    //if point is NULL return, nothing to do
    if (point == NULL) {
        return;
    }

    for (int i = 0; i < buttonArray->size(); ++i) {

        if (buttonArray->at(i)->pointInsideArea(point) == 1) {

            switch (buttonArray->at(i)->getMode()) {
                case MOMENTARY:
                    callAction(buttonArray->at(i)->getAction());
                    break;
                case TOGGLE:
                    callAction(buttonArray->at(i)->getAction());
                    break;
                case PICKER:
                    break;
                default:
                    break;
            }

        }
    }

    for (int i = 0; i < fileTable->size(); ++i) {

        if (fileTable->at(i)->pointInsideArea(point) == 1) {

            screenInterpreter->getScribbleArea()->getSender()->sendDownloadFile(fileTable->at(i)->getFileName());

            while (screenInterpreter->getScribbleArea()->getNetworkActivity() == ScribbleArea::NetworkActivity::WAITING_FOR_FILE_DOWNLOAD);

            screenInterpreter->showFilelist(0);

#warning //show download alert
        }
    }

    delete point;
    point = NULL;
}

/*! Screen Move Event
 *
 * \param *point A pointer to a Point object
 *
 * This function draws a line between a last point and the new point in Write mode or tries to delete a path on which the point passes through in Erase mode
 */
void FileList::screenMoveEvent(Point* point) {

}

/*! Screen Release Event
 *
 * This function disables scribbling and informs the ScribbleArea that nothing is touching the screen anymore
 */
void FileList::screenReleaseEvent(/*Points *point*/) {

}

void FileList::callAction(int action) {

    switch (action) {
        case NEW_DOCUMENT_FL:
            std::cout << "new_document" << std::endl;
            break;
        case NEXT_PAGE_FL:

            if (page < numberOfPages - 1) {
                page += 1;

                start = page * 10;

                if (page + 1 == numberOfPages) {
                    size = fileList.size() % 10;
                }
                else {
                    size = 10;
                }

                createTable();
            }

            break;
        case PREVIOUS_PAGE_FL:

            if (page > 0) {
                page -= 1;

                start = page * 10;

                if (page + 1 == numberOfPages) {
                    size = fileList.size() % 10;
                }
                else {
                    size = 10;
                }

                createTable();
            }

            break;
        default:
            break;
    }

}

void FileList::setScreenInterpreter(ScreenInterpreter *s) {
    screenInterpreter = s;
}

std::vector <FileListButton *> * FileList::getButtonArray() {
    return buttonArray;
}

std::vector <std::string> FileList::getFileList() {
    return fileList;
}

void FileList::setFileList(std::vector <std::string> fl) {
    fileList = fl;

    numberOfPages = (fileList.size() / 10) + 1;
    std::cout<<fileList.size();
    
    if (fileList.size() <= 10) {
        size = fileList.size();
    } else {
        size = 10;
    }

    createTable();
}

std::vector <FileListCell *> *FileList::getFileListTable() {
    return fileTable;
}

void FileList::createTable() {

    int type = MOMENTARY;
    int action = SELECTED_CELL_C;
    int btnx = 0;
    int btny = 60;
    int btnw = 656;
    int btnh = 62;

    for (uint i = 0; i < fileTable->size(); i++) {
        delete fileTable->at(i);
    }

    fileTable->clear();

    for (uint i = 0; i < size; ++i) {
        FileListCell *cell = new FileListCell(btnx + x, btny * (i + 1) + 2 * i + y, btnw, btnh, type, action, NULL, NULL, NULL, NULL, fileList.at(start + i), start + i);
        fileTable->push_back(cell);
    }
}

std::string FileList::getNumberOfPages() {
    std::stringstream ss;
    ss << numberOfPages;
    return ss.str();
}

std::string FileList::getCurrentPage() {
    
    std::stringstream ss;
    ss << page+1;
    return ss.str();
}